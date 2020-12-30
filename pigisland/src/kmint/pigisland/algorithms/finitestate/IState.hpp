#pragma once
#include <string>

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            template <typename T>
            class IState
            {
            public:
                virtual ~IState() = default;

                virtual void entry(T& entity) = 0;
                virtual void execute(T& entity) = 0;
                virtual void exit(T& entity) = 0;

                virtual std::string toString() = 0;
            };
        }
    }
}