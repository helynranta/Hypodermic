project(Hypodermic LANGUAGES CXX)

include(GNUInstallDirs)

set(HEADER_FILES
        ActivatedRegistrationInfo.h
        ActivationException.h
        ActivationHandler.h
        ActivationHandlers.h
        ActivationRegistry.h
        ActivationResult.h
        AnyArgument.h
        ArgumentPack.h
        ArgumentResolver.h
        As.h
        AsSelf.h
        AutowireableConstructor.h
        AutowireableConstructorRegistrationDescriptor.h
        Behavior.h
        CircularDependencyException.h
        ComponentContext.h
        Config.h
        ConsoleLoggerSink.h
        ConstructorDescriptor.h
        ConstructorTypologyDeducer.h
        Container.h
        ContainerBuilder.h
        ContainerInstanceRegistration.h
        ContainerInstanceRegistrationActivator.h
        DependencyActivationException.h
        DependencyFactories.h
        DependencyFactory.h
        DependencyFactoryTag.h
        EnforceBaseOf.h
        EnforceDependencyNotAlreadyRegistered.h
        ExceptionBase.h
        FactoryWrapper.h
        Hypodermic.h
        HypodermicExport.h
        ILoggerSink.h
        IMutableRegistrationScope.h
        InstanceAlreadyActivatingException.h
        InstanceFactory.h
        InstanceLifetime.h
        InstanceRegistrationTags.h
        IntegerSequence.h
        IRegistration.h
        IRegistrationActivator.h
        IRegistrationDescriptor.h
        IRegistrationRegistry.h
        IRegistrationScope.h
        IResolutionContainer.h
        IResolutionContext.h
        IRuntimeRegistrationBuilder.h
        IsComplete.h
        IsSupportedArgument.h
        ITypeAlias.h
        Log.h
        Logger.h
        LogLevel.h
        MetaContains.h
        MetaForEach.h
        MetaIdentity.h
        MetaInsert.h
        MetaMap.h
        MetaPair.h
        Named.h
        NamedTypeAlias.h
        NestedRegistrationScope.h
        NoopLoggerSink.h
        OnActivated.h
        PersistentInstanceRegistration.h
        PointerAlignment.h
        Pragmas.h
        ProvidedDependencyTag.h
        ProvidedInstanceDependencyTag.h
        ProvidedInstanceFactoryRegistrationDescriptor.h
        ProvidedInstanceRegistration.h
        ProvidedInstanceRegistrationActivator.h
        ProvidedInstanceRegistrationDescriptor.h
        Registration.h
        RegistrationActivator.h
        RegistrationBuilder.h
        RegistrationContext.h
        RegistrationDescriptorBase.h
        RegistrationDescriptorBuilder.h
        RegistrationDescriptorInfo.h
        RegistrationDescriptorInfoToString.h
        RegistrationException.h
        RegistrationScope.h
        ResolutionContainer.h
        ResolutionContext.h
        ResolutionException.h
        ResolutionInfo.h
        RuntimeRegistrationBuilder.h
        SingleInstance.h
        TypeAlias.h
        TypeAliases.h
        TypeAliasKey.h
        TypeInfo.h
        UseIfNone.h
        With.h)

add_library(${PROJECT_NAME} INTERFACE ${HEADER_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_include_directories(
    ${PROJECT_NAME}
        INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(
        TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-config
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/
)

install(
        EXPORT ${PROJECT_NAME}-config DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Hypodermic
)

install(
        DIRECTORY ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.hpp*" PATTERN "*.inl*" PATTERN "*.h*"
)
