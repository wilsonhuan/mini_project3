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
    if(state->legal_actions.empty())state->get_legal_actions();
    auto actions = state->legal_actions;
    int index=0;
    int max=-100000;
    for(int i=0;i<(int)actions.size();i++){
        auto value = find_value(state->next_state(actions[i]),depth-1,false);
        if(value > max){
            max = value;
            index = i;
        }
    }
    return actions[index];
}
int Minimax::find_value(State* state, int depth, bool max){
    state->get_legal_actions();
    if(depth == 0 || state->legal_actions.size() == 0){
        int value = state->evaluate(state->player);
        return value;
    }
    else if(max){
        int value = -100000;
        for(int i=0; i<(int)state->legal_actions.size(); i++){
            auto nextvalue = find_value(state->next_state(state->legal_actions[i]), depth-1, false);
            if(nextvalue >= value){
                value = nextvalue;
            }
        }
        return value;
    }
    else{
        int value = 100000;
        for(int i=0; i<(int)state->legal_actions.size(); i++){
            auto nextvalue = find_value(state->next_state(state->legal_actions[i]), depth-1, true);
            if(nextvalue <= value){
                value = nextvalue;
            }
        }
        return value;
    }
}