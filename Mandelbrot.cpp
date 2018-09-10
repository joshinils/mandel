#include "olcPixelGameEngine.h"
#include <iostream>

const int MAXITERS = 100;

template <typename zahl>
size_t mandelbrot(const zahl& rC, const zahl& iC)
{
	size_t iters = 0;
	zahl rZ = 0;
	zahl iZ = 0;

	while (++iters < MAXITERS && rZ*rZ + iZ*iZ < 4)
	{
		// malnehmen
		// Z = (rZ + iZ)^2 + (rC + iC)
		// Z = (rZ + I*iZ)(rZ + I*iZ) + (rC + I*iC)
		// Z = rZ*rZ + 2*IiZ*rZ + I^2*iZ^2 + (rC + I*iC)
		// Z = rZ*rZ + rC - iZ^2   +   2*I*iZ*rZ + I*iC

		static zahl oldrZ = rZ;
		oldrZ = rZ;
		// rZ <- rZ*rZ + rC - iZ^2

		rZ = rZ*rZ + rC - iZ*iZ;
		//rZ *= rZ;
		//rZ += rC - iZ*iZ;

		// iZ <- 2*iZ*rZ + iC
		iZ = 2 * iZ*oldrZ + iC;
		//iZ *= 2*oldrZ;
		//iZ += iC;
	}

	return iters;
}

template <typename zahl>
class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Mandelbrot";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		static zahl wh = (zahl)ScreenWidth() / 2;
		static zahl wv = wh / 2;

		static zahl hh = (zahl)ScreenHeight() / 2;
		static zahl hv = hh / 2;

		// called once per frame
		static int sw = ScreenWidth();
		static int sh = ScreenHeight();
		for (int x = 0; x < sw; ++x)
			for (int y = 0; y < sh; ++y)
			{
				size_t iters = mandelbrot<zahl>((x -wh)/wv , (y - hh) / hv );
			//	std::cout << "x" << x << " y" << y << "  iters" << iters << "   at:" << (x - (double)ScreenWidth() / 2) / (ScreenWidth() / 2) << "  " << (y - ScreenHeight() / 2) / (ScreenHeight() / 2) << std::endl;
				Draw(x, y, olc::Pixel(iters, iters, iters));
			}
	//	std::cout << std::endl;
		return true;
	}
};


int main()
{
	Example<double> demo;
	if (demo.Construct(400, 400, 1, 1))
		demo.Start();

	return 0;
}
