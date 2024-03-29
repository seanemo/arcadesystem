#include "SimpleButton.h"

SimpleButton::SimpleButton()
{
	setTexturePath("");
	setWidth(0);
	setHeight(0);
	setX(0);
	setY(0);

	buttonAction = nullptr;
	buttonTexture = nullptr;
}

// override constructor
SimpleButton::SimpleButton(std::string imagePath_in) 
{
	setTexturePath(imagePath_in);

	buttonAction = nullptr;
	buttonTexture = nullptr;
}

SimpleButton::~SimpleButton()
{
	delete buttonAction;
	delete buttonTexture;
}

// UPDATE
// if the event is a tab or arrow key, then increment the button selector by one
// if the event is enter, then return the button's action and actionParameter
Action SimpleButton::update(SDL_Event* event)
{
	// at the end we return newAction. We initialize it to do nothing and change it based on the event
	Action newAction = { DO_NOTHING, nullptr };

	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Check if mouse is in button
	bool inside = true;

	//Mouse is left of the button
	if (x < getX())
	{
		inside = false;
	}
	//Mouse is right of the button
	else if (x > getX() + getWidth())
	{
		inside = false;
	}
	//Mouse above the button
	else if (y < getY())
	{
		inside = false;
	}
	//Mouse below the button
	else if (y > getY() + getHeight())
	{
		inside = false;
	}
	if (!inside)
	{
		buttonTexture->setSelected(false);
	}
	else
	{
		buttonTexture->setSelected(true);
	}

	if (event && (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP))
	{
		//Mouse is outside button
		if (!inside)
		{
			buttonTexture->setSelected(false);
		}
		else
		{
			//Set mouse over sprite
			switch (event->type)
			{
			case SDL_MOUSEMOTION:
				buttonTexture->setSelected(true);
				break;

			case SDL_MOUSEBUTTONDOWN:
				printf("MOUSE CLICKED ====================================================");
				newAction = *getButtonAction();
				break;
				break;

				/*case SDL_MOUSEBUTTONUP:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
					break;*/
			}
		}
	}
	return newAction;
}

// RENDER
// simply call the ArcadeTexture render method on the button's texture
void SimpleButton::render(SDL_Renderer* renderer)
{
	//printf("current button texture   %p \n", getButtonTexture());
	getButtonTexture()->render(renderer);
}



