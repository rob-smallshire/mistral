/*
 * BothFansFromFanBState.hpp
 *
 *  Created on: 23 Sep 2012
 *      Author: rjs
 */

#ifndef BOTHFANSFROMFANB_HPP_
#define BOTHFANSFROMFANB_HPP_

#include <state/bothfansstate.hpp>

class BothFansFromFanBState : public BothFansState {
public:
    BothFansFromFanBState(Controller* ctxt);
    ~BothFansFromFanBState();

	virtual State* transitionHigher();
	virtual State* transitionLower();
	virtual const char* name();
};


#endif /* BOTHFANSFROMFANB_HPP_ */
