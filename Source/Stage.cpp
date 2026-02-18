#include "Stage.h"
#include <cassert>

Stage::Stage()
{
	hModel = MV1LoadModel("data/models/Stage/Stage00.mv1");
	assert(hModel > 0);
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	MV1DrawModel(hModel);
}
