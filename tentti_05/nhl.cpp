// nhl.cpp
#include "nhl.h"
#include <algorithm>  // sort esim.
#include <fstream>    // tiedostojen luku
#include <sstream>
#include <string>
#include <iomanip>

namespace otecpp_nhl {


  // toiminnee positiivisilla
  int strToInt(std::string& str) {

    int num;
    std::istringstream(str) >> num;
    return num;

  }


  Date::Date(int d, int m, int y) : day_(d), month_(m), year_(y) {
    // ...
  }

  int Date::day() const {
    return this->day_;
  }

  int Date::month() const {
    return this->month_;
  }

  int Date::year() const {
    return this->year_;
  }

  // varhaisempi päivämäärä on pienempi
  bool Date::operator<(Date& d) {
    // jos pvm sama, jatka kuukauden tark.
    if( this->year() == d.year() ) {
      // jos kuukausi sama, vertaile suoraan päivää
      if( this->month() == d.month() ) {
        return this->day() < d.day();
      } else {
        return this->month() < d.month();
      }
    } else {
      return this->year() < d.year();
    }

  }


  std::ostream& operator<<(std::ostream& stream, const Date& d) {
    stream << d.day() << "." << d.month() << "." << d.year();
    return stream;
  }




  // Player

  Player::Player(int id, int team_id, std::string name, char pos, std::string country, Date birthday) 
  : id_(id), team_id_(team_id), name_(name), pos_(pos), country_(country), bday(birthday) {

  }

  int Player::id() const { return this->id_; }

  int Player::team_id() const { return this->team_id_; }

  const std::string& Player::name() const { return this->name_; }

  char Player::position() const { return this->pos_; }

  const std::string& Player::country() const { 
    return this->country_; 
  }

  const Date& Player::birthDate() const  { return this->bday; }

  // TODO: Syntymäpäivä
  bool Player::operator<(Player& p) {

    if(this->name() == p.name()) {
      // Same, by ID
      return this->id() < p.id();
    }
    else {
      return this->name() < p.name();
    }
    return false;

  }

  // "nimi; joukkue; syntymämaa; syntymäaika"
  // TODO: hae tiimin nimi kun ID tiedetään!
  std::ostream& operator<<(std::ostream& stream, const Player& p) {
    stream << p.name() << "; " << "TEAM NAME; " << p.country() << "; " << p.birthDate();
    return stream;
  }





  Stat::Stat(int player_id, int assists,  int goals, int games, int pm) : player_id_(player_id), assists_(assists),  goals_(goals), games_(games), plus_minus_(pm) {

  }

  int Stat::player_id() const { return this->player_id_; }

  int Stat::assists() const { return this->assists_; }

  int Stat::games() const {
    return this->games_;
  }

  int Stat::goals() const { return this->goals_; }

  int Stat::plus_minus() const {
    return this->plus_minus_;
  }

  int Stat::points() const {
    return this->goals_ + this->assists_;
  } 

  double Stat::ppg() const {
    return this->points() / this->games();
  }



  // TODO:
  std::ostream& operator<<(std::ostream& virta, const Stat& s) {
    
    std::setprecision(2); // tulostaa kaikki intitkin?

    virta << s.goals()+s.assists() << " points, " << s.goals() << " goals" << s.assists() << "assists, " << s.ppg() << "points per game, plus/minus: " << s.plus_minus();

    return virta;
  }



  // -- STATS --

  Stat Stats::stat(int player_id) const {
    // Iteroi läpi ja jos id matchaa, palauta se
    for(std::vector<Stat>::const_iterator itr = this->stats_.begin(); itr != this->stats_.end(); ++itr) {
      if( itr->player_id() == player_id ) {
        return *itr;
      }
    }
    // muutoin...
    return Stat(player_id, 0, 0, 0, 0);
  }

  void Stats::push(Stat stat) {
    this->stats_.push_back( stat );
  }

  /**
   * Muut sallitut order-arvot ovat: goals, assists, points_per_game (ks. teht.anto)
   * order="points"
   */ 
  std::vector<Stat> Stats::statsBy(std::string order) const {

    /*if(order == "points") {
      

      std::sort( this->stats_.begin(), this->stats_.end(), cmpPlayerPoints);
    }
    else if(order=="goals") {
      // 
      std::sort(this->stats_.begin(), this->stats_.end(), cmpPlayerGoals);
    }
    else if(order=="assists") {
      // 
      std::sort( this->stats_.begin(), this->stats_.end(), cmpPlayerAssists);
    }
    else if(order=="points_per_game") {
      std::sort( this->stats_.begin(), this->stats_.end(), cmpPlayerPointsPerGame);
    }
    else {
      // Muutoin ID:n mukaan
      std::sort( this->stats_.begin(), this->stats_.end(), cmpPlayerId);
    }
    */

    return this->stats_;

  }






  // -- TEAM --

  Team::Team(int id, std::string abbr, std::string name) : id_(id), abbreviation_(abbr), name_(name) {
  } 

  int Team::id() const { this->id_; }

  const std::string& Team::abbreviation() const { return this->abbreviation_; }

  const std::string& Team::name() const { return this->name_; }

  // Luettelee pelaajat nimien kasvavan aakkosjärjestyksen mukaisessa järjestyksessä
  const std::vector<Player>& Team::players() const { 
    
    //std::sort( this->players_.begin(), this->players_.end() );  // käyttää vertainta <
    return this->players_;

  }

  /**
   * vertailee joukkueita nimen perusteella. Jos nimet olisivat samat, verrataan toissijaisesti id-numeroita.
   */
  bool Team::operator<(Team& team) {

    if(this->name() != team.name()) {
      return this->name() < team.name();
    } 
    else {
      return this->id() < team.id();
    }

  }

  std::ostream& operator<<(std::ostream& stream, const Team& t) {
    stream << t.name() << "(" << t.abbreviation() << ")";
    return stream;
  }





  // -- League --

  League::League(std::string joukkuetiedosto, std::string pelaajatiedosto, std::string tilastotiedosto) {

    // Lue data: TODO:
    std::vector< std::vector<std::string> > teamData   = lueTiedosto(joukkuetiedosto); // id, lyhenne, nimi
    std::vector< std::vector<std::string> > playerData = lueTiedosto(pelaajatiedosto); // id, joukkuenimi, id;joukkueen id;nimi; pelipaikka; syntymämaa; syntymäaika
    std::vector< std::vector<std::string> > statsData  = lueTiedosto(tilastotiedosto); // pelaajan id; syötöt; maalit; pelit; plus-miinus



    // Luo kutakin tiedoston riviä vastaavat oliot for-loopeissa ja tallenna
    for (size_t t_i=0; t_i < teamData.size(); t_i++) {
      
      // Luo tiimi-olio
      Team tiimi( 
        strToInt(teamData.at(t_i).at(0)),
        teamData.at(t_i).at(1),
        teamData.at(t_i).at(2)
      );

      this->teams_.push_back( tiimi );

    }


    // Sama Playereille
    for (size_t p_i=0; p_i < teamData.size(); ++p_i) {
      
      // Luo pelaaja-olio
      Player pelaaja( 
        strToInt( playerData.at(p_i).at(0) ), // id
        strToInt( playerData.at(p_i).at(1) ), // team id
        playerData.at(p_i).at(2),               // name
        playerData.at(p_i).at(3).c_str()[0], // pos
        playerData.at(p_i).at(4), // counrty
        Date(1,1,1970)  //playerData.at(p_i).at(5) // b.day , TODO:  PARSI BDAY 
      );

      this->players_.push_back( pelaaja );

    }


    // Ja sama statseille
    for (size_t s_i=0; s_i < statsData.size(); ++s_i) {

      // Yksittäinen Stat-olio
      Stat statsi(
        strToInt( statsData.at(s_i).at(0) ), // p id
        strToInt( statsData.at(s_i).at(1) ), // syötöt
        strToInt( statsData.at(s_i).at(2) ), // maalit
        strToInt( statsData.at(s_i).at(3) ), // pelit
        strToInt( statsData.at(s_i).at(4) ) // +-
      );

      this->stats_.push( statsi );

    }


  }



  const std::vector<Team>& League::teams() const {
    //std::sort( this->teams_.begin(), this->teams_.end(), cmpTeamsAbbr );
    return this->teams_;
  }

  const std::vector<Player>& League::players() const {
    return this->players_;
  }

  const Stats& League::stats() const {
    this->stats_;
  }





    // Apumetodi joka lukee erotinmerkillä erotetut asiat vektoriin
  std::vector<std::string> split(const std::string erotin,  std::string rivi) {

    int position = 0;
    std::string found = "";
    std::vector<std::string> tulos;

    while ((position = rivi.find(erotin)) != std::string::npos) {
      found = rivi.substr(0, position);
      tulos.push_back(found);
      rivi.erase(0, position + erotin.length());
    }
    tulos.push_back( rivi ); // viimeinen 

    return tulos;


  }


  /**
   * Lukee tiedoston jonka tied.nimen saa param.
   * Palauttaa kunkin rivin vektorina, tulos on siis 2d-vektori, jossa
   * 0. indeksi kuvaa 1. riviä jne... 
   */
  std::vector< std::vector<std::string> > lueTiedosto( const std::string filename) {

    std::ifstream ifs( filename.c_str() );
    std::vector< std::vector<std::string> > tulos; // 2d-vek
    std::string rivi; // lue rivi tänne

    if(ifs) {
      while( getline(ifs, rivi, '\n') ) {
        tulos.push_back( split(";", rivi) );
      }
    }

    return tulos;

  }


    /* Vertaimet. Saa param kaksi pelaajan statsi-oliota.
  
    Kaikissa tapauksissa toissijainen lajittelukriteeri on pelaajan id-numero
     (eli esim. maaleihin perustuvassa listassa saman maalimäärän omaavat laitettaisiin id-numeroiden mukaan laskevaan järjestykseen)

   */

  // Oletusvertain. ID:n mukaan
  bool cmpPlayerId(const Stat& s1, const Stat& s2) { 
    return s1.player_id() < s2.player_id();
  }

  bool cmpPlayerPoints(const Stat& s1, const Stat& s2) { 

    int p1_p = s1.goals() + s1.assists();
    int p2_p = s2.goals() + s2.assists();

    if( p1_p == p2_p ) { return cmpPlayerId(s1,s2); }
    return p1_p < p2_p;
  }

  bool cmpPlayerGoals(const Stat& s1, const Stat& s2) { 
    if( s1.goals() == s2.goals() ) { 
       return cmpPlayerId(s1,s2);
    }
    return s1.goals() < s2.goals();
  }

  bool cmpPlayerAssists(const Stat& s1, const Stat& s2) { 
    if(  s1.assists() == s2.assists()) {
      return  cmpPlayerId(s1,s2);
    }
    return s1.assists() < s2.assists();
  }


  bool cmpPlayerPointsPerGame(const Stat& s1, const Stat& s2) { 
    if(  s1.ppg() == s2.ppg() ) {
      return  cmpPlayerId(s1,s2);
    }
    return s1.ppg()  <  s2.ppg();
  }

  bool cmpTeamsAbbr(const Team& t1, const Team& t2) {
    return t1.abbreviation() < t2.abbreviation();
  }

}