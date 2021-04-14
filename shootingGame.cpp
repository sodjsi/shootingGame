#define _CRT_SECURE_NO_WARNINGS
#include<bangtal.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

SceneID background, scene;
ObjectID startbutton, howtoplay, goal, title, heart[5], scene2, endbutton, restart;
TimerID timer;
int count = 0;
int score = 0;
int random_x, random_y;
int life = 4;
bool game_life = false;

void game_end()
{
	hideObject(goal);
	if (life == -1)
	{
		showMessage("실패하셨습니다! 지금까지의 기록은 콘솔 창을 확인해주세요!\n왼쪽 버튼은 종료, 오른쪽 버튼은 재시작입니다.");
		printf("걸린 시간 : %d초\n", count);
		printf("맞춘 과녁 : %d개\n", score);
	}
	else
	{
		showMessage("감사합니다! 클리어하는 데에 걸린 시간은 콘솔 창을 확인해주세요!\n왼쪽 버튼은 종료, 오른쪽 버튼은 재시작입니다.");
		printf("걸린 시간 : %d초", count);
	}
	showObject(endbutton);
	showObject(restart);
}

void game_start()
{
	scaleObject(goal, 0.3f);
	do {
		random_x = rand() % 600 + 1;
		random_y = rand() % 600 + 1;
	} while (random_x < 120 || random_y < 120);
	locateObject(goal, scene, random_x, random_y);
	showObject(goal);
	hideObject(endbutton);
	hideObject(restart);
}

void timerCallback(TimerID timer)
{
	count++;
	setTimer(timer, 1.f);
	startTimer(timer);
}



SceneID game_init()
{
	background = createScene("", "scene.png");
	scene = createScene("", "scene.png");

	scene2 = createObject("scene.png");
	locateObject(scene2, scene, 0, 0);
	showObject(scene2);

	startbutton = createObject("start.png");
	locateObject(startbutton, background, 520, 150);
	showObject(startbutton);
	scaleObject(startbutton, 0.5f);

	howtoplay = createObject("howtoplay.png");
	locateObject(howtoplay, background, 520, 100);
	showObject(howtoplay);
	scaleObject(howtoplay, 0.235f);

	goal = createObject("과녁.png");
	locateObject(goal, scene, 100, 200);
	hideObject(goal);

	title = createObject("background.jpg");
	locateObject(title, background, 520, 400);
	scaleObject(title, 0.5f);
	showObject(title);

	endbutton = createObject("exit.png");
	locateObject(endbutton, scene, 450, 400);
	scaleObject(endbutton, 0.32f);
	hideObject(endbutton);

	restart = createObject("restart.png");
	locateObject(restart, scene, 650, 400);
	scaleObject(restart, 0.125f);
	hideObject(restart);

	for (int i = 0; i < 5; i++)
	{
		heart[i] = createObject("heart.png");
		locateObject(heart[i], scene, 30 * i, 720);
		scaleObject(heart[i], 0.05f);
		showObject(heart[i]);
	}

	return background;
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (object == startbutton)
	{
		game_start();
		enterScene(scene);
		startTimer(timer);
		game_life = true;
	}
	else if (object == howtoplay)
	{
		showMessage("무작위로 생성되는 20개의 과녁을 클릭하여 없애는 게임입니다! 목숨은 5개 입니다!");
	}
	else if (object == goal)
	{
		game_start();
		if (score == 19)
		{
			game_end();
		}
		score++;
	}
	else if (object == restart)
	{
		game_life = false;
		enterScene(game_init());
	}
	else if (object == endbutton)
	{
		endGame();
	}
	else if (action == MouseAction::MOUSE_CLICK && game_life)
	{
		hideObject(heart[life]);
		life--;
		if (life == -1)
		{
			game_end();
		}
	}
}

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, true);
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	srand(time(NULL));

	timer = createTimer(1.f);

	startGame(game_init());

}