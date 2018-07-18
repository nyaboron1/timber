#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void updateBranches (int seed);

const int NUM_BRANCHES = 6;

Sprite branches [NUM_BRANCHES];

enum class side {LEFT, RIGHT, NONE};

side branchPositions [NUM_BRANCHES];

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
  Texture tBranch;
  tBranch.loadFromFile("resources/graphics/branch.png");
  
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
  // set the texture each branch sprite
  for (int i = 0; i < NUM_BRANCHES; ++i)
    {
      branches[i].setTexture(tBranch);
      branches[i].setPosition(-2000,-2000);
      branches[i].setOrigin(220,20);
    }

  
  Font font;
  font.loadFromFile("resources/fonts/KOMIKAP_.ttf");

  Text messageText;
  messageText.setFont(font);
  messageText.setString("Press Enter to start");
  messageText.setCharacterSize(75);
  messageText.setFillColor(Color::White);
  messageText.setPosition(1920/2, 1080/2);
  Text scoreText;
  scoreText.setFont(font);
  scoreText.setString("Score = 0");
  scoreText.setCharacterSize(100);
  scoreText.setFillColor(Color::White);
  scoreText.setPosition(20, 20);

  FloatRect textRect = messageText.getLocalBounds();
  messageText.setOrigin(textRect.left +
			 textRect.width / 2.0f,
			 textRect.top +
			 textRect.height / 2.0f);
  
  /****************************
    Variables
  *****************************/
  bool beeActive = false;
  bool cloud1Active = false;
  bool cloud2Active = false;
  bool cloud3Active = false;
  bool cloud4Active = false;
  bool pause = true; // game running
  
  float beeSpeed = 0.0f;
  float cloud1Speed = 0.0f;
  float cloud2Speed = 0.0f;
  float cloud3Speed = 0.0f;
  float cloud4Speed = 0.0f;

  int score = 0; 
  
  Clock clock;

  // Time bar
  RectangleShape timeBar;

  float timeBarStartWidth = 400;
  float timeBarHeight = 80;

  timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
  timeBar.setFillColor(Color::Red);
  timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

  Time gameTimeTotal;
  float timeRemaining = 6.0f;
  float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
  
  while (window.isOpen())
    {
      /*******************************
	Handle the players input
      ********************************/
      if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
	  window.close();
	}

      // start he game
      if (Keyboard::isKeyPressed(Keyboard::Return))
	{
	  pause = false;

	  // reset de time and the score
	  score = 0;
	  timeRemaining = 5;
	}

      /*******************************
	Update the scene
      *******************************/
      if (!pause)
	{
	  Time dt = clock.restart(); // delta time

	  // Subtract from the amount of time remaining
	  timeRemaining -= dt.asSeconds();
	  // size up the time bar
	  timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				   timeRemaining, timeBarHeight));

	  if (timeRemaining <= 0.0f)
	    {
	      // pase the game
	      pause = true;

	      // change the message shown to the player
	      messageText.setString("Out of time");

	      // Reposition the text
	      FloatRect textRect = messageText.getLocalBounds();
	      messageText.setOrigin
		(textRect.left +
		 textRect.width / 2.0f,
		 textRect.top + textRect.height / 2.0f);

	      messageText.setPosition(1920 / 2, 1080 / 2);
	    }
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
	}
      
      // Update the score text
      std::stringstream ss;
      ss << "Score = " << score;
      scoreText.setString(ss.str());

      // Update the branch sprites
      for (int i = 0; i < NUM_BRANCHES; ++i)
	{
	  float height = i * 150;
	  if (branchPositions[i] == side::LEFT)
	    {
	      // move the sprite to the left side
	      branches[i].setPosition(610,height);
	      // Flip the msprite round the other way
	      branches[i].setRotation(180);
	    }
	  else if (branchPositions[i] == side::RIGHT)
	    {
	      branches[i].setPosition(1330,height);
	      branches[i].setRotation(0);
	    }
	  else
	    {
	      // Hide the branch
	      branches[i].setPosition(3000, height);
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
      window.draw(scoreText);
      window.draw(timeBar);
      // draw branches
      for (int i = 0; i < NUM_BRANCHES; ++i)
	{
	  window.draw(branches[i]);
	}
      
      if (pause)
	  window.draw(messageText);
      
      window.display();
    }

  return 0;
}
