#include "graphics/window.h"
#include "graphics/spriteBatcher.h"

int main(void)
{
	int WINDOW_WIDTH = 1024;
	int WINDOW_HEIGHT = 768;

	Window window("OpenGL Studies", WINDOW_WIDTH, WINDOW_HEIGHT, true);

	SpriteBatcher* spriteBatcher = new SpriteBatcher(glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture* texture = new Texture("resources/images/texture.png");
	texture->IncRefCount();

	while (window.isOpen())
	{
		window.clear();

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				for (int k = 0; k < 10; k++)
				{
					spriteBatcher->Draw(glm::vec4(100 + i * 50 + k * -10, 100 + j * 50 + k * -10, 50, 50), glm::vec4(0, 0, 300, 320), glm::vec4(i / 10.f, j / 10.f, k / 10.f, 1), texture);
					// Uncomment this line to see how much slower it is to call draw separately for each sprite.
					//spriteBatcher->Flush();
				}
			}
		}
		// Now that we have a collection of all the draws we want to make, send it all to the gpu to be drawn!
		spriteBatcher->Flush();

		window.update();
	}

	delete spriteBatcher;

	texture->DecRefCount();

	return 0;
}
