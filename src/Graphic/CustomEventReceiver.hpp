//
// Created by jdecombe on 09/05/18.
//

#ifndef IRRLICHTTESTS_CUSTOMEVENTRECEIVER_HPP
#define IRRLICHTTESTS_CUSTOMEVENTRECEIVER_HPP

#include "Irrlicht/irrlicht.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CustomEventReceiver : public IEventReceiver {
	private:
		bool _keyIsDown[KEY_KEY_CODES_COUNT];


	public:
		CustomEventReceiver();
		virtual ~CustomEventReceiver();
		bool OnEvent(const SEvent &event) override;
		bool isKeyDown(EKEY_CODE keyCode) const;
};

#endif //IRRLICHTTESTS_CUSTOMEVENTRECEIVER_HPP
