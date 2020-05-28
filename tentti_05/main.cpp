#ifndef NHL_H
  #include "nhl.h"
#endif // NHL_H
#include <algorithm>
#include <iomanip>
#include <map>
#include <stdio.h>
#include <vector>


using otecpp_nhl::Date;
using otecpp_nhl::League;
using otecpp_nhl::Player;
using otecpp_nhl::Stat;
using otecpp_nhl::Stats;
using otecpp_nhl::Team;
using namespace std;

int main(int argc, char *argv[]) {
  
  League league(argv[1], argv[2], argv[3]);

  Stats stats = league.stats();    
  vector<Team> teams = league.teams();
  
  
  for(unsigned i = 0; i < teams.size(); ++i) {
    cout << teams[i] << endl;
    const vector<Player>& players = teams[i].players();

    // DEBUG
    //cout << "tiimissä pelaajia " << teams[i].players().size() << std::endl;
    //cout << players.size() << "pelaajaa tiimissa...\n";

    for(unsigned j = 0; j < players.size(); ++j) {
      cout << players[j] << endl;
      cout << stats.stat(players[j].id()) << endl << endl; // !
    }
    cout << endl << endl;
  }
  

  
  
  sort(teams.rbegin(), teams.rend());
  for(unsigned i = 0; i < teams.size(); ++i) {
    cout << teams[i].id() << " " << teams[i].abbreviation() << " "
         << teams[i].name() << endl;
  }
  cout << endl << endl;


  
  vector<Date> dates;
  vector<Player> players = league.players();
  for(unsigned i = 0; i < players.size(); ++i) {
    cout << players[i] << endl;
    dates.push_back(players[i].birthDate());
  }
  cout << endl << endl;

  
  sort(players.rbegin(), players.rend());
  for(unsigned i = 0; i < players.size(); ++i) {
    cout << players[i].id() << " " << players[i].team_id() << " "
         << players[i].name() << " " << players[i].position() << " "
         << players[i].country() << " " << players[i].birthDate() << endl;
  }
  cout << endl << endl;


  
  std::map<int, std::vector<Player>::size_type> playerMap;
  for(unsigned int i = 0; i < players.size(); ++i) {
    playerMap[players[i].id()] = i;
  }
  
  
  vector<Stat> stat_vec = league.stats().statsBy();
  for(unsigned i = 0; i < stat_vec.size(); ++i) {
    cout << players[playerMap[stat_vec[i].player_id()]] << endl;
    cout << "points: " << stat_vec[i].goals() + stat_vec[i].assists()
         << endl << endl;
  }
  cout << endl << endl;
  
  
  stat_vec = league.stats().statsBy("goals");
  for(unsigned i = 0; i < stat_vec.size(); ++i) {
    cout << players[playerMap[stat_vec[i].player_id()]] << endl;
    cout << "goals: " << stat_vec[i].goals() << endl << endl;
  }
  cout << endl << endl;
  
  stat_vec = league.stats().statsBy("assists");
  for(unsigned i = 0; i < stat_vec.size(); ++i) {
    cout << players[playerMap[stat_vec[i].player_id()]] << endl;
    cout << "assists: " << stat_vec[i].assists() << endl << endl;
  }
  cout << endl << endl;
  
  stat_vec = league.stats().statsBy("points_per_game");
  for(unsigned i = 0; i < stat_vec.size(); ++i) {
    cout << players[playerMap[stat_vec[i].player_id()]] << endl;
    float ppg = 0;
    if(stat_vec[i].games() > 0) {
      ppg = stat_vec[i].assists() + stat_vec[i].goals();
      ppg /= stat_vec[i].games();
    }
    cout << "points per game: " << fixed << setprecision(2)
         << ppg << endl << endl;
  }
  cout << endl << endl;
  
  
  sort(dates.begin(), dates.end());
  for(unsigned i = 0; i < dates.size(); ++i) {
    cout << dates[i].day() << "." << dates[i].month() << "."
         << dates[i].year() << " == " << dates[i] << endl;
  }
  cout << endl << endl;

  
  
  return 0;
}