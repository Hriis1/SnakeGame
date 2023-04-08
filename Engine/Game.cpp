/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	_board(gfx), _rng(std::random_device()()), _snek({10,10}), _goal(_rng, _board, _snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!_gameOver) {
		if (wnd.kbd.KeyIsPressed(VK_UP) && _delta_loc!=Location(0,1))
		{
			_delta_loc = { 0,-1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN) && _delta_loc != Location(0, -1))
		{
			_delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT) && _delta_loc != Location(1, 0))
		{
			_delta_loc = { -1,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT) && _delta_loc != Location(-1, 0))
		{
			_delta_loc = { 1,0 };
		}

		_snekMoveCounter++;
		if (_snekMoveCounter >= _snekMovePeriod)
		{
			_snekMoveCounter = 0;
			Location next = _snek.GetNextHeadPos(_delta_loc);
			if (_board.isInsideBoard(next) && !_snek.IsInTileExeptEnd(next))
			{
				bool eating = next == _goal.getLocation();
				if (eating)
				{
					_snek.Grow();
				}
				_snek.MoveBy(_delta_loc);
				if (eating)
				{
					_goal.Respawn(_rng, _board, _snek);
				}
			}
			else
			{
				_gameOver = true;
			}

		}
	}
		
}

void Game::ComposeFrame()
{
	_board.DrawBorder(Color(87, 9, 70));
	_snek.Draw(_board);
	_goal.Draw(_board);

	if (_gameOver)
	{
		SpriteCodex::DrawGameOver(Graphics::ScreenWidth/2 - 50, Graphics::ScreenHeight/2 - 50, gfx);
	}
}
