#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
  VideoMode vm(1920, 1080);
  RenderWindow window(vm, "Timber :O");

  /*****************************
    Preparar scene
  ******************************/
  Texture tBack;
  tBack.loadFromFile("resources/graphics/background.png");
  
  Texture tTree;
  tTree.loadFromFile("resources/graphics/tree.png");

  Texture tBee;
  tBee.loadFromFile("resources/graphics/bee.png");

  
  Sprite sBack;
  sBack.setTexture(tBack);
  sBack.setPosition(0, 0);

  Sprite sTree;
  sTree.setTexture(tTree);
  sTree.setPosition(810, 0);

  Sprite sBee;
  sBee.setTexture(tBee);
  sBee.setPosition(0, 800);

  /****************************
    Variables
  *****************************/
  bool beeActive = false;
  float beeSpeed = 0.0f;
  
  Clock clock;
  
  while (window.isOpen())
    {
      /*******************************
	Handle the players input
      ********************************/
      if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
	  window.close();
	}

      /*******************************
	Update the scene
      *******************************/
      Time dt = clock.restart(); // delta time

      // update bee
      if (!beeActive)
	{
	  // how fast is the bee
	  srand ((int)time(0));
	  beeSpeed = (rand() % 200) + 200;

	  // how high is the bee
	  srand ((int)time(0) * 10);
	  float height = (rand() % 500) + 500;
	  sBee.setPosition (200, height);
	  beeActive = true;
	}
      // move the bee
      else
	{
	  sBee.setPosition
	    (sBee.getPosition().x -
	     (beeSpeed * dt.asSeconds()),
	     sBee.getPosition().y
	     );
	  // bee reached the right hand
	  if (sBee.getPosition().x < -100)
	    {
	      // set ready for update
	      beeActive = false;
	    }

	}
      
      /*******************************
	Draw the scene
      *******************************/
      window.clear();

      window.draw(sBack);
      window.draw(sTree);
      window.draw(sBee);

      window.display();
    }

  return 0;
}
