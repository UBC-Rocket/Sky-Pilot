#ifndef STATES__ARMED_H
#define STATES__ARMED_H

/*Includes------------------------------------------------------------*/
#include "state_interface.h"
#include "state_input_struct.h"

namespace State {

    class Armed : IState {
    public:
        Armed(const ascent_id, int const ARMED_CHECKS, int const LAUNCH_THRESHOLD) :
              m_ascent_id(ascent_id)
            , M_ARMED_CHECKS(ARMED_CHECKS)
            , M_LAUNCH_THRESHOLD(LAUNCH_THRESHOLD) {}

        /*
        * @brief Return the assigned enumeration code.
        * @return Enumeration code.
        */
        StateId getStateEnum(void){ return StateId::ARMED; }

        /*
        * @brief Return the next state, based on input data (mostly from filtered sensor data)
        * @return State enumeration code, to be passed into the std::map between codes and used states. Note that the returned code may be the same state.
        */
        StateId getNewState(StateInput const &input, StateAuxilliaryInfo &state_aux);

    private:
        StateId m_ascent_id;
        int M_ARMED_CHECKS;
        int M_LAUNCH_THRESHOLD;
    }

}
#endif
