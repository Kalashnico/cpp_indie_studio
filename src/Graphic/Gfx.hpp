//
// Created by jdecombe on 08/05/18.
//

#ifndef INC_1_GFX_HPP
#define INC_1_GFX_HPP

#include <string>
#include <unordered_map>
#include "Irrlicht/irrlicht.h"

#define WIN_WIDTH	600
#define WIN_HEIGHT	400

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Gfx {
	private:
		IrrlichtDevice *_device;
		IVideoDriver *_videoDriver;
		IGUIEnvironment *_guiEnv;
		ISceneManager *_sceneManager;
		IEventReceiver *_eventReceiver;
		std::unordered_map<std::string, ISceneNode *> _nodeCache;

	public:
		Gfx();

		explicit Gfx(IEventReceiver &receiver);

		virtual ~Gfx();

		void update();

		bool isRunning();

		void drawStaticText(stringw const &str, rect<s32> const &pos);

		ISceneManager *getSceneManager() const;

		IAnimatedMeshSceneNode *drawMesh(std::string const &path,
			std::string const &material, bool lighting,
			const std::string &name,
			const vector3df &pos = {0.0f, 0.0f, 0.0f},
			const vector3df &scale = {1.0f, 1.0f, 1.0f}
		);

		void addCameraFPS();

		void setEventReceiver(IEventReceiver &receiver);

		bool isKeyDown(EKEY_CODE keyCode) const;

		void moveElement(std::string const &name, vector3df const &vec,
			float speed = 100.0
		);

		void rotateElement(std::string const &name, vector3df const &vec
		);

		void deleteElement(std::string const &name);

		void addLight(vector3df const &pos, SColorf const &color,
			float radius = 1000.0f
		);


};

#endif //INC_1_GFX_HPP
