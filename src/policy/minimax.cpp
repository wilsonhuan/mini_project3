#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;
    int index = 0;
    int max = 0;
    for (int i = 0; i < (int)state->legal_actions.size(); i++){
        int value = state->next_state(actions[i])->evaluate(state->player);
        if(value > max){
            max = value;
            index = i;
        }
    }
    return actions[index];
}