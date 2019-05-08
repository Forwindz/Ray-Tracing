#include "Precompile.h"
#include "RayTracingMath.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "MaterialMetal.h"
#include "MaterialDielectric.h"

std::unique_ptr<rd::Canvas> canvas;
std::unique_ptr<rd::Camera> camera;
std::unique_ptr<rd::Scene> scene;
void printProcess(const int x, const int maxx, std::string&& info="Processing ")
{
	int percentX = x * 100 / maxx;
	int percentForward = (x-1) * 100 / maxx;
#ifdef USE_MSAA_SAMPLE
	if (percentX != percentForward)
#endif
	{
		std::cout << info << "[ \t" << x << "\t|\t" << maxx << "] \t" << percentX << "%\r";
	}
}

constexpr int maxDepth = 50;

rtm::Vec3 calcRay(const rtm::Ray3 ray,const rtm::Vec2 centerPos, const int depth = 0)
{
	const rtm::RtmGeneralType a = 1 - (centerPos.y + 1)*0.5;
	rd::HitRecord hr;
	const bool hit = scene->rayHit(ray, 0.001, 100, hr);
	if (hit)
	{
		rtm::Ray3 scatterRay;
		rtm::Vec3 attenuation;
		if (depth < maxDepth && hr.hitObject->matPtr->scatter(ray, hr, attenuation, scatterRay))
		{
			return attenuation * calcRay(scatterRay, centerPos, depth + 1);
		}
	}
	return rtm::Vec3(0.5 + 0.5*a, 0.7 + 0.3*a, 1);
}


int main(int argc, char** argv)
{
	canvas = std::make_unique<rd::Canvas>();
	scene = std::make_unique<rd::Scene>();
	camera = std::make_unique<rd::Camera>();

	canvas->fillColor({ 0,0,0 });

	camera->width = canvas->getWidth();
	camera->height = canvas->getHeight();
	camera->fov = 60 / 180.0*3.1415926;
	camera->zNear = 1.0;
	camera->pos = { 0,0,0 };
	camera->setView({ 1,0,0 }, { 0,0,1 });
	
	camera->update();
	
	scene->addHitable(new rd::Sphere(rtm::Vec3(15, 0, 0),		1,		new rd::MaterialDielectric({ 1.0, 1.0, 0.9 },1.7)));
	scene->addHitable(new rd::Sphere(rtm::Vec3(12, -3, -0.2),	1,		new rd::MaterialLambertian({ 0.3,0.8,0.3 })));
	scene->addHitable(new rd::Sphere(rtm::Vec3(15, 2.1, 0),		1,		new rd::MaterialLambertian({ 0.3,0.8,0.3 })));
	scene->addHitable(new rd::Sphere(rtm::Vec3(10, -5, -0.04),	1,		new rd::MaterialMetal({ 0.3,0.3,0.8 }, 0.3)));
	scene->addHitable(new rd::Sphere(rtm::Vec3(10, 6, -0.5),	1,		new rd::MaterialDielectric({ 0.6, 0.4, 0.9 }, 1.4)));
	scene->addHitable(new rd::Sphere(rtm::Vec3(25, -2, 5),		1,		new rd::MaterialLambertian({ 0.8,0.8,0.3 })));
	scene->addHitable(new rd::Sphere(rtm::Vec3(20, 0, -35.5),	35.0,	new rd::MaterialLambertian({ 0.8,0.3,0.3 })));

	const int jitterCount = 200;
	const rtm::RtmGeneralType jitterDiv = 1 / static_cast<rtm::RtmGeneralType>(jitterCount);
	const auto pixelSize = camera->getPixelSize();
	const rtm::RtmGeneralType lenRadius = 2;
	for (int i = 0; i < canvas->getHeight(); ++i)
	{
		printProcess(i, canvas->getHeight());
		for (int j = 0; j < canvas->getWidth(); ++j)
		{
			const auto centerPos = camera->getCenterPos(j, i);
			auto& pixel = canvas->at(j, i);
			pixel = rtm::Vec3(0);
			for (int k = 0; k < jitterCount; k++)
			{
				const auto realCenterPos = centerPos + camera->getJitterPos()*lenRadius;

				pixel += calcRay(camera->getRayCenterPos(realCenterPos.x, realCenterPos.y), realCenterPos);
			}
			pixel *= jitterDiv;
			pixel = rtm::pow(pixel, 1/2.0);
		}
	}
	std::cout << "\nComplete! Saving...";
	canvas->saveBMP("test.bmp");
	std::cout << "Save complete!";
	return 0;
}