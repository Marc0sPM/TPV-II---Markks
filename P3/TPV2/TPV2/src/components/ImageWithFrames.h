// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL.h>

#include "../ecs/Component.h"

class Texture;
class Transform;

class ImageWithFrames : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::IMAGEWITHFRAMES)

		ImageWithFrames(Texture* tex, //
			int cols, int rows, //
			int x, int y, //
			int fW, int fH, //
			int scol, int srow, // 
			int ncol, int nrow,
			Uint32 timeBetweenFrames = 50);
	virtual ~ImageWithFrames();
	void initComponent() override;
	void render() override;
	// cambia el frame tanto columnas y filas
	inline void changeFrames(int srow, int scol) {
		scol_ = scol;
		srow_ = srow;
	}

	// cambia solo las columnas de la animacion
	inline void changeFrames(int scol) {
		scol_ = scol;
	}
	Texture *tex_;
private:
	Transform *tr_;
	int currFrameR_;
	int currFrameC_;
	int x_;
	int y_;
	int frameWidth_;
	int frameHeight_;
	int srow_;
	int scol_;
	int nrow_;
	int ncol_;
	Uint32 lastFrameChange_;
	Uint32 timeBetweenFrames_;
};

