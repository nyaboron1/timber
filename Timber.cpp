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
  Texture tCloud;
  tCloud.loadFromFile("resources/graphics/cloud.png");
  
  Sprite sBack;
  sBack.setTexture(tBack);
  sBack.setPosition(0, 0);
  Sprite sTree;
  sTree.setTexture(tTree);
  sTree.setPosition(810, 0);
  Sprite sBee;
  sBee.setTexture(tBee);
  
  Sprite sCloud1;
  sCloud1.setTexture(tCloud);
  Sprite sCloud2;
  sCloud2.setTexture(tCloud);
  Sprite sCloud3;
  sCloud3.setTexture(tCloud);
  Sprite sCloud4;
  sCloud4.setTexture(tCloud);

  /****************************
    Variables
  *****************************/
  bool beeActive = false;
  bool cloud1Active = false;
  bool cloud2Active = false;
  bool cloud3Active = false;
  bool cloud4Active = false;
  
  float beeSpeed = 0.0f;
  float cloud1Speed = 0.0f;
  float cloud2Speed = 0.0f;
  float cloud3Speed = 0.0f;
  float cloud4Speed = 0.0f;
  
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
	  float high = (rand() % 1920);
	  sBee.setPosition (high, height);
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

      
      if (!cloud1Active)
	{
	  // how fast is the cloud
	  srand((int)time(0) * 10);
	  cloud1Speed = (rand() % 200);

	  // how high is the cloud
	  srand((int)time(0) * 10);
	  float height = (rand() % 150);
	  sCloud1.setPosition(-200, height);
	  cloud1Active = true;
	}
      else
	{
	  sCloud1.setPosition
	    (sCloud1.getPosition().x +
	     (cloud1Speed * dt.asSeconds()),
	     sCloud1.getPosition().y);

	  if (sCloud1.getPosition().x > 1920)
	    {
	      cloud1Active = false;
	    }
	}

      
      if (!cloud2Active)
	{
	  // how fast is the cloud
	  srand((int)time(0) * 20);
	  cloud2Speed = (rand() % 200);

	  // how high is the cloud
	  srand((int)time(0) * 20);
	  float height = (rand() % 300) - 150;
	  sCloud2.setPosition(-200, height);
	  cloud2Active = true;
	}
      else
	{
	  sCloud2.setPosition
	    (sCloud2.getPosition().x +
	     (cloud2Speed * dt.asSeconds()),
	     sCloud2.getPosition().y);

	  if (sCloud2.getPosition().x > 1920)
	    {
	      cloud2Active = false;
	    }
	}

      if (!cloud3Active)
	{
	  // how fast is the cloud
	  srand((int)time(0) * 10);
	  cloud3Speed = (rand() % 300);

	  // how high is the cloud
	  srand((int)time(0) * 10);
	  float height = (rand() % 450) - 150;
	  sCloud3.setPosition(-200, height);
	  cloud3Active = true;
	}
      else
	{
	  sCloud3.setPosition
	    (sCloud3.getPosition().x +
	     (cloud3Speed * dt.asSeconds()),
	     sCloud3.getPosition().y);

	  if (sCloud3.getPosition().x > 1920)
	    {
	      cloud3Active = false;
	    }
	}

      
      /*******************************
	Draw the scene
      *******************************/
      window.clear();

      window.draw(sBack);
      window.draw(sTree);
      window.draw(sBee);
      window.draw(sCloud1);
      window.draw(sCloud2);
      window.draw(sCloud3);
      
      window.display();
    }

  return 0;
}
