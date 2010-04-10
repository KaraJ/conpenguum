#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QStringList>
#include <string>
#include <sstream>
#include <stdlib.h>

class Player
{
public:
	Player(int id, std::string name) : id_(id), kills_(0), deaths_(0), streak_(0), name_(name) { }
	Player(std::string data)
	{
		QStringList player = QString(data.c_str()).split(",", QString::SkipEmptyParts);
		id_ = atoi(player[0].toStdString().c_str());
		name_ = player[1].toStdString();
		kills_ = atoi(player[2].toStdString().c_str());
		deaths_ = atoi(player[3].toStdString().c_str());
		streak_ = atoi(player[4].toStdString().c_str());
	}
	Player(){}
	void addDeath() { deaths_++; streak_ = 0; }
	void addKill() { kills_++; streak_++; }
	int getId() const { return id_; }
	int getKills() const { return kills_; }
	std::string getKillsString() const { std::ostringstream oss; oss << kills_; return oss.str();}
	std::string getDeathsString() const { std::ostringstream oss; oss << deaths_; return oss.str();}
	int getDeaths() const { return deaths_; }
	int getStreak() const { return streak_; }
	std::string getName() const { return name_; }
	friend inline std::ostream& operator<<(std::ostream&, const Player&);
	friend inline bool operator<(const Player &, const Player&);

private:
	int id_, kills_, deaths_, streak_;
	std::string name_;
};

std::ostream& operator<<(std::ostream& os, const Player& p)
{
	return os << p.id_ << "," << p.name_ << "," << p.kills_ << "," << p.deaths_ << "," << p.streak_;
}

bool operator<(const Player &p1, const Player &p2)
{
	return (p1.kills_ < p2.kills_) || (p1.name_ < p2.name_);
}

#endif
