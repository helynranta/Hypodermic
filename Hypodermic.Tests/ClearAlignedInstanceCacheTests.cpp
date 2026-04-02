#include "stdafx.h"

#include "Hypodermic/ContainerBuilder.h"

#include "TestingTypes.h"


namespace Hypodermic
{
namespace Testing
{

    BOOST_AUTO_TEST_SUITE(ClearAlignedInstanceCacheTests)

    BOOST_AUTO_TEST_CASE(should_clear_cache_on_flat_container)
    {
        // Arrange
        ContainerBuilder builder;
        builder.registerType< DefaultConstructible1 >().as< DefaultConstructibleBase >().singleInstance();

        auto container = builder.build();

        auto instance1 = container->resolve< DefaultConstructibleBase >();
        BOOST_REQUIRE(instance1 != nullptr);

        // Act
        container->clearAlignedInstanceCache();

        // Assert — resolve still works after clear
        auto instance2 = container->resolve< DefaultConstructibleBase >();
        BOOST_REQUIRE(instance2 != nullptr);
        // singleInstance: same activation, just re-aligned
        BOOST_CHECK(instance1 == instance2);
    }

    BOOST_AUTO_TEST_CASE(should_clear_cache_on_parent_from_nested_container)
    {
        // Arrange
        ContainerBuilder builder;
        builder.registerType< DefaultConstructible1 >().as< DefaultConstructibleBase >().singleInstance();

        auto container = builder.build();

        auto instance1 = container->resolve< DefaultConstructibleBase >();
        BOOST_REQUIRE(instance1 != nullptr);

        // Nested container resolves from parent — populates parent's alignment cache
        {
            ContainerBuilder nestedBuilder;
            nestedBuilder.registerType< DefaultConstructible2 >();
            auto nestedContainer = nestedBuilder.buildNestedContainerFrom(*container);

            auto parentInstanceFromNested = nestedContainer->resolve< DefaultConstructibleBase >();
            BOOST_CHECK(parentInstanceFromNested == instance1);
        }

        // Act — clear the parent's cache
        container->clearAlignedInstanceCache();

        // Assert — parent still resolves fine
        auto instance2 = container->resolve< DefaultConstructibleBase >();
        BOOST_REQUIRE(instance2 != nullptr);
        BOOST_CHECK(instance1 == instance2);
    }

    BOOST_AUTO_TEST_CASE(should_clear_cache_on_nested_container)
    {
        // Arrange
        ContainerBuilder builder;
        builder.registerType< DefaultConstructible1 >().as< DefaultConstructibleBase >().singleInstance();

        auto container = builder.build();

        ContainerBuilder nestedBuilder;
        nestedBuilder.registerType< DefaultConstructible2 >().as< DefaultConstructibleBase >().singleInstance();
        auto nestedContainer = nestedBuilder.buildNestedContainerFrom(*container);

        auto nestedInstance = nestedContainer->resolve< DefaultConstructibleBase >();
        BOOST_REQUIRE(nestedInstance != nullptr);

        // Act — clear from nested container (propagates to parent)
        nestedContainer->clearAlignedInstanceCache();

        // Assert — both containers still resolve
        auto nestedInstance2 = nestedContainer->resolve< DefaultConstructibleBase >();
        BOOST_REQUIRE(nestedInstance2 != nullptr);
        BOOST_CHECK(nestedInstance == nestedInstance2);

        auto parentInstance = container->resolve< DefaultConstructibleBase >();
        BOOST_REQUIRE(parentInstance != nullptr);
    }

    BOOST_AUTO_TEST_CASE(should_resolve_after_nested_destroy_and_cache_clear)
    {
        // This simulates the plugin reload scenario:
        // 1. Build engine (parent) container
        // 2. Build plugin (nested) container
        // 3. Resolve from nested (populates parent cache with plugin TypeAliasKeys)
        // 4. Destroy nested container
        // 5. Clear parent's cache
        // 6. Build new nested container
        // 7. Resolve again — must work without crash

        ContainerBuilder parentBuilder;
        parentBuilder.registerType< DefaultConstructible1 >().as< DefaultConstructibleBase >().singleInstance();
        parentBuilder.registerType< TopLevelConstructor >();

        auto parentContainer = parentBuilder.build();

        // Cycle 1
        {
            ContainerBuilder nestedBuilder;
            nestedBuilder.registerInstance(std::make_shared< NestedDependency >(42));
            auto nestedContainer = nestedBuilder.buildNestedContainerFrom(*parentContainer);

            auto instance = nestedContainer->resolve< TopLevelConstructor >();
            BOOST_REQUIRE(instance != nullptr);
            BOOST_CHECK_EQUAL(instance->dependency->i, 42);

            auto baseInstance = nestedContainer->resolve< DefaultConstructibleBase >();
            BOOST_REQUIRE(baseInstance != nullptr);
        }

        // Cache clear between cycles (simulates reload)
        parentContainer->clearAlignedInstanceCache();

        // Cycle 2
        {
            ContainerBuilder nestedBuilder;
            nestedBuilder.registerInstance(std::make_shared< NestedDependency >(99));
            auto nestedContainer = nestedBuilder.buildNestedContainerFrom(*parentContainer);

            auto instance = nestedContainer->resolve< TopLevelConstructor >();
            BOOST_REQUIRE(instance != nullptr);
            BOOST_CHECK_EQUAL(instance->dependency->i, 99);

            auto baseInstance = nestedContainer->resolve< DefaultConstructibleBase >();
            BOOST_REQUIRE(baseInstance != nullptr);
        }
    }

    BOOST_AUTO_TEST_CASE(should_survive_multiple_clear_cycles)
    {
        // Stress test: repeated nested create/destroy/clear cycles

        ContainerBuilder parentBuilder;
        parentBuilder.registerType< DefaultConstructible1 >().as< DefaultConstructibleBase >().singleInstance();

        auto parentContainer = parentBuilder.build();

        for (int i = 0; i < 10; ++i)
        {
            ContainerBuilder nestedBuilder;
            nestedBuilder.registerType< DefaultConstructible2 >();
            auto nestedContainer = nestedBuilder.buildNestedContainerFrom(*parentContainer);

            auto instance = nestedContainer->resolve< DefaultConstructibleBase >();
            BOOST_CHECK(instance != nullptr);

            nestedContainer.reset();
            parentContainer->clearAlignedInstanceCache();
        }

        // Parent still works after all cycles
        auto finalInstance = parentContainer->resolve< DefaultConstructibleBase >();
        BOOST_CHECK(finalInstance != nullptr);
    }

    BOOST_AUTO_TEST_CASE(should_clear_resolveAll_alignment_cache)
    {
        // resolveAll also populates alignment caches

        ContainerBuilder parentBuilder;
        parentBuilder.registerType< DefaultConstructible1 >().as< DefaultConstructibleBase >();

        auto parentContainer = parentBuilder.build();

        ContainerBuilder nestedBuilder;
        nestedBuilder.registerType< DefaultConstructible2 >().as< DefaultConstructibleBase >();
        auto nestedContainer = nestedBuilder.buildNestedContainerFrom(*parentContainer);

        auto all = nestedContainer->resolveAll< DefaultConstructibleBase >();
        BOOST_REQUIRE_EQUAL(all.size(), 2u);

        nestedContainer.reset();
        parentContainer->clearAlignedInstanceCache();

        // Parent still resolves its own registration
        auto parentInstance = parentContainer->resolve< DefaultConstructibleBase >();
        BOOST_CHECK(parentInstance != nullptr);
    }

    BOOST_AUTO_TEST_CASE(clear_on_empty_container_is_safe)
    {
        // Calling clearAlignedInstanceCache on a container that has never resolved anything
        ContainerBuilder builder;
        builder.registerType< DefaultConstructible1 >();

        auto container = builder.build();
        BOOST_CHECK_NO_THROW(container->clearAlignedInstanceCache());

        // Still resolves fine
        auto instance = container->resolve< DefaultConstructible1 >();
        BOOST_CHECK(instance != nullptr);
    }

    BOOST_AUTO_TEST_SUITE_END()

} // namespace Testing
} // namespace Hypodermic
