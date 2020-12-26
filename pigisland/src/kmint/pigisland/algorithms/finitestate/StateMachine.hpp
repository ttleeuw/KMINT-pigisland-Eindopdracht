#pragma once
#include "kmint/pigisland/algorithms/finitestate/IState.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            template <typename T>
            class StateMachine
            {
            private:
                std::unique_ptr<IState<T>> currentState;
                std::unique_ptr<IState<T>> globalState;
            public:
                void setCurrentState(std::unique_ptr<IState<T>> _state, T& entity) {
                    this->currentState = std::move(_state);
                    this->currentState->entry(entity);
                };
                
                void setGlobalState(std::unique_ptr<IState<T>> _globalState, T& entity) {
                    this->globalState = std::move(_globalState);
                    this->globalState->entry(entity);
                };

                void update(T& entity) {
                    this->currentState->execute(entity);
                    this->globalState->execute(entity);
                };

                void changeState(std::unique_ptr<IState<T>> _state, T& entity) {
                    if (currentState != _state && _state);

                    currentState->exit(entity);
                    currentState = std::move(_state);
                    currentState->entry(entity);
                };
            };
        }
    }
}