/*
 * BothFansFromFanAState.hpp
 *
 *  Created on: 23 Sep 2012
 *      Author: rjs
 */

#ifndef BOTHFANSFROMFANA_HPP_
#define BOTHFANSFROMFANA_HPP_

#include <state/BothFansState.hpp>

class BothFansFromFanAState : public BothFansState {
public:
    BothFansFromFanAState(Controller* ctxt);
    ~BothFansFromFanAState();

	virtual State* transitionHigher();
	virtual State* transitionLower();
};


#endif /* BOTHFANSFROMFANA_HPP_ */
