#ifndef		HYPODERMIC_COMPONENT_REGISTRY_H_
# define	HYPODERMIC_COMPONENT_REGISTRY_H_

# include <memory>
# include <typeindex>
# include <unordered_map>
# include <vector>

# include <boost/thread.hpp>

# include <Hypodermic/IComponentRegistry.h>
# include <Hypodermic/ServiceRegistrationInfo.h>


namespace Hypodermic
{
    class IComponentRegistration;


	class ComponentRegistry : public IComponentRegistry
	{
		typedef std::unordered_map< std::type_index, std::shared_ptr< ServiceRegistrationInfo > > ServiceRegistrationInfos;

	public:
		IComponentRegistration* getRegistration(std::shared_ptr< Service > service);

		bool isRegistered(std::shared_ptr< Service > service);

		void addRegistration(IComponentRegistration* registration);

        void addRegistration(IComponentRegistration* registration, bool preserveDefaults);

		std::vector< IComponentRegistration* > registrations();

		std::vector< IComponentRegistration* > registrationsFor(std::shared_ptr< Service > service);

		std::shared_ptr< ServiceRegistrationInfo > getServiceInfo(std::shared_ptr< Service > service);

		std::shared_ptr< ServiceRegistrationInfo > getInitializedServiceInfo(std::shared_ptr< Service > service);

	private:
		std::vector< IComponentRegistration* > registrations_;
		ServiceRegistrationInfos serviceInfo_;
		boost::recursive_mutex mutex_;
	};

} // namespace Hypodermic


#endif /* !HYPODERMIC_COMPONENT_REGISTRY_H_ */