#include <SFML/Graphics.hpp>

#include <sstream>

using namespace sf;



const int NUM_BRANCHES = 6;

enum class side
  {
   LEFT,
   RIGHT,
   NONE
  };

Sprite branches[NUM_BRANCHES];

side branchPositions [NUM_BRANCHES];



void updateBranches (int seed)
{
  // move branches down one place
  for (int i = NUM_BRANCHES; i > 0; --i)
    {
      branchPositions[i] = branchPositions[i-1];
    }

  // spawn a new branch at position 0
  srand((int)time(0) + seed);

  int r = (rand() % 5);

  if (r == 0)
    {
      branchPositions[0] = side::LEFT;
    }
  else if (r == 1)
    {
      branchPositions[0] = side::RIGHT;
    }
  else
    {
      branchPositions[0] = side::NONE;
    }
}


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
  Texture tPlayer;
  tPlayer.loadFromFile("resources/graphics/player.png");
  Texture tAxe;
  tAxe.loadFromFile("resources/graphics/axe.png");
  Texture tLog;
  tLog.loadFromFile("resources/graphics/log.png");
  Texture tRip;
  tRip.loadFromFile("resources/graphics/rip.png");

  
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
  Sprite sPlayer;
  sPlayer.setTexture(tPlayer);
  sPlayer.setPosition(580,720);
  Sprite sAxe;
  sAxe.setTexture(tAxe);
  sAxe.setPosition(700,830);
  Sprite sLog;
  sLog.setTexture(tLog);
  sLog.setPosition(810,720);
  Sprite sRip;
  sRip.setTexture(tRip);
  sRip.setPosition(600,860);
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

  RectangleShape timeBar;

  float timeBarStartWidth = 400;
  float timeBarHeight = 80;

  timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
  timeBar.setFillColor(Color::Red);
  timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

  Time gameTimeTotal;
  float timeRemaining = 6.0f;
  float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

  // player side
  side playerSide = side::LEFT;

  // log
  int logSpeedX = 1000;
  int logSpeedY = -1500;
  bool logActive = false;

  // axe
  const float axePositionLeft = 700.0f;
  const float axePositionRight = 1075.0f;

  // control the player input
  bool acceptInput = false;
  
  while (window.isOpen())
    {
      /*******************************
	Handle the players input
      ********************************/

      Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == Event::KeyReleased && !pause)
	    {
	      // Listen for key presses again
	      acceptInput = true;

	      // hide the axe
	      sAxe.setPosition(2000, sAxe.getPosition().y);
	    }
	}

      
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

	  // make all the branches disappear
	  for (int i = 1; i < NUM_BRANCHES; ++i)
	    {
	      branchPositions[i] = side::NONE;
	    }

	  // make sure the gravestone is hidden
	  sRip.setPosition(675, 2000);

	  // move the player into position
	  sPlayer.setPosition(580, 720);

	  acceptInput = true;
	}

      // wrap the player constrols
      if (acceptInput)
	{
	  // Handle pressing the right cursor key
	  if (Keyboard::isKeyPressed(Keyboard::Right))
	    {
	      playerSide = side::RIGHT;
	      score++;

	      // Add to the amount of time remaining
	      timeRemaining += (2 / score) + 0.15f;

	      sAxe.setPosition(axePositionRight,
			       sAxe.getPosition().y);

	      sPlayer.setPosition(1200,720);

	      // update the brances
	      updateBranches(score);

	      // set the log flying to the left
	      sLog.setPosition(810,720);
	      logSpeedX = -5000;
	      logActive = true;

	      acceptInput = false;
	    }
	  else if (Keyboard::isKeyPressed(Keyboard::Left))
	    { 
	      playerSide = side::LEFT;
	      score++;

	      // Add to the amount of time remaining
	      timeRemaining += (2 / score) + 0.15f;

	      sAxe.setPosition(axePositionLeft,
			       sAxe.getPosition().y);

	      sPlayer.setPosition(580,720);

	      // update the brances
	      updateBranches(score);

	      // set the log flying to the left
	      sLog.setPosition(810,720);
	      logSpeedX = 5000;
	      logActive = true;

	      acceptInput = false;
	    }
	    
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

	      // Handle a flying log
	      if (logActive)
		{
		  sLog.setPosition(sLog.getPosition().x +
				   (logSpeedX * dt.asSeconds()),
				   sLog.getPosition().y +
				   (logSpeedY * dt.asSeconds()));

		  // Has the log reached the right hand edge?
		  if (sLog.getPosition().x < -100 ||
		      sLog.getPosition().x > 2000)
		    {
		      // set it up ready
		      logActive = false;
		      sLog.setPosition(810, 720);
		    }
		}
	    }
	  
	}
      
      /*******************************
	Draw the scene
      *******************************/
      window.clear();
      window.draw(sBack);
      window.draw(sCloud1);
      window.draw(sCloud2);
      window.draw(sCloud3);
      window.draw(sTree);

      for (int i = 0; i < NUM_BRANCHES; i++)
	{
	  window.draw(branches[i]);
	}
      
      window.draw(sPlayer);
      window.draw(sAxe);
      window.draw(sLog);
      window.draw(sRip);
      window.draw(sBee);
      window.draw(scoreText);
      window.draw(timeBar);
      window.draw(scoreText);
      window.draw(timeBar);
      
      if (pause)
	  window.draw(messageText);
      
      window.display();
    }

  return 0;
}
