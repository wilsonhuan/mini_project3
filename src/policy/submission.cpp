#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move submission::get_move(State *state, int depth){
    if(state->legal_actions.empty())state->get_legal_actions();
    auto actions = state->legal_actions;
    int index=0;
    int max=-100000;
    for(int i=0;i<(int)actions.size();i++){
        auto value = find_value(state->next_state(actions[i]),depth-1,-100000,100000,false);
        if(value > max){
            max = value;
            index = i;
        }
    }
    return actions[index];
}
int submission::find_value(State* state, int depth, int alpha, int beta, bool max){
    state->get_legal_actions();
    int alpha_ = alpha;
    int beta_ = beta;
    if(depth == 0 || state->legal_actions.size() == 0){
        int value = state->evaluate(state->player);
        return value;
    }
    else if(max){
        int value = -100000;
        for(int i=0; i<(int)state->legal_actions.size(); i++){
            auto nextvalue = find_value(state->next_state(state->legal_actions[i]), depth-1, alpha_, beta_, false);
            if(nextvalue >= value){
                value = nextvalue;
            }
            if(nextvalue > alpha_){
                alpha_ = nextvalue;
            }
            if(alpha_ >= beta_){
                break;
            }
        }
        return value;
    }
    else{
        int value = 100000;
        for(int i=0; i<(int)state->legal_actions.size(); i++){
            auto nextvalue = find_value(state->next_state(state->legal_actions[i]), depth-1, alpha_, beta_, true);
            if(nextvalue <= value){
                value = nextvalue;
            }
            if(beta_ < nextvalue){
                beta_ = nextvalue;
            }
            if(alpha_ >= beta_){
                break;
            }
        }
        return value;
    }
}