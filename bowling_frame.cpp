#include "bowling_frame.h"
#include <random>

std::random_device dev;
std::mt19937 rng(dev());

Bowling_Frame::Bowling_Frame(int fnum)
{
	score1_ = 0;
	score2_ = 0;
	score3_ = 0;
	strike_ = false;
	spare_ = false;
	roll_one_ = false;
	roll_two_ = false;
	roll_three_ = false;
	frame_num_ = fnum;
	frame_score_ = 0;

	next_frame_ = nullptr;
	prev_frame_ = nullptr;
}

Bowling_Frame::~Bowling_Frame()
{
	delete next_frame_;
}

Bowling_Frame* Bowling_Frame::next_frame() { return next_frame_; }
void Bowling_Frame::next_frame( Bowling_Frame * new_frame ) { next_frame_ = new_frame; }

Bowling_Frame* Bowling_Frame::prev_frame() { return prev_frame_; }
void Bowling_Frame::prev_frame( Bowling_Frame * new_frame ) { prev_frame_ = new_frame; }

int Bowling_Frame::score1()				{ return score1_; }
void Bowling_Frame::score1( int score )	{ score1_ = score; }

int Bowling_Frame::score2()				{ return score2_; }
void Bowling_Frame::score2( int score )	{ score2_ = score; }

int Bowling_Frame::score3()				{ return score3_; }
void Bowling_Frame::score3( int score )	{ score3_ = score; }

bool Bowling_Frame::strike() 			{ return strike_; }
void Bowling_Frame::strike(bool value )	{ strike_ = value; }

bool Bowling_Frame::spare() 			{ return spare_; }
void Bowling_Frame::spare(bool value )	{ spare_ = value; }

int Bowling_Frame::frame_num()			{ return frame_num_; }
int Bowling_Frame::frame_score()		{ return frame_score_; }

int Bowling_Frame::next_rolls(int count)
{
	int sum = 0;
	Bowling_Frame * f = next_frame_;

	while (f && count > 0)
	{
		sum += f->score1_;
		count--;

		if (count > 0 && (!f->strike_ || f->frame_num_ == 10))
		{
			sum += f->score2_;
			count--;
		}

		if (count > 0 && f->frame_num_ == 10)
		{
			sum += f->score3_;
			count--;
		}

		f = f->next_frame_;
	}
	return sum;
}

void Bowling_Frame::update_scores()
{
	if (!roll_one_)
	{
		std::uniform_int_distribution<int> dist(0, 10);
		score1_ = dist(rng);
		roll_one_ = true;

		if (score1_ == 10) strike_ = true;
	}
	else if (frame_num_ == 10)
	{
		if (!roll_two_)
		{
			int max_pins = strike_ ? 10 : 10 - score1_;
			std::uniform_int_distribution<int> dist(0, max_pins);
			score2_ = dist(rng);
			roll_two_ = true;

			if (!strike_ && (score1_ + score2_) == 10) spare_ = true;
		}
		else if (!roll_three_ && (strike_ || spare_))
		{
			int max_pins = 10;
			if (strike_ && score2_ < 10) max_pins = 10 - score2_;

			std::uniform_int_distribution<int> dist(0, max_pins);
			score3_ = dist(rng);
			roll_three_ = true;
		}
	}
	else if (!strike_ && !roll_two_)
	{
		std::uniform_int_distribution<int> dist(0, 10 - score1_);
		score2_ = dist(rng);
		roll_two_ = true;

		if ((score1_ + score2_) == 10) spare_ = true;
	}
	else if (next_frame_)
	{
		next_frame_->update_scores();
	}

	frame_score_ = score1_ + score2_ + score3_;
	if (frame_num_ < 10)
	{
		if (strike_)     frame_score_ += next_rolls(2);
		else if (spare_) frame_score_ += next_rolls(1);
	}
}
