#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(int id, std::string name), id_(id), name_(name), kills_(0), deaths_(0), streak_(0) { }
	void addDeath() { kills_++; streak_ = 0; }
	void addKill() { kills_++; streak_++; }
	int getId() const { return id_; }
	int getKills() const { return kills_; }
	int getDeaths() const { return deaths_; }
	int getStreak() const { return streak_; }
	std::string getName() const { return name_; }

private:
	int id_, kills_, deaths_, streak_;
	std::string name_;
};

#endif
