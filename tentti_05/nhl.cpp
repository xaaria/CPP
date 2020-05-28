// nhl.cpp
#include "nhl.h"
#include <algorithm>  // sort esim.
#include <fstream>    // tiedostojen luku
#include <sstream>
#include <string>
#include <iomanip>



namespace otecpp_nhl {


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
  bool Date::operator<(const Date& d) const {
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

  Player::Player(int id, int team_id, std::string name, char pos, std::string country, Date birthday)  // team...
  : id_(id), team_id_(team_id), name_(name), pos_(pos), country_(country), bday(birthday) { //team(t) {

  }

  int Player::id() const { return this->id_; }
  int Player::team_id() const { return this->team_id_; }
  const std::string& Player::name() const { return this->name_; }
  char Player::position() const { return this->pos_; }
  const std::string& Player::country() const { return this->country_; }
  const Date& Player::birthDate() const  { return this->bday; }

  bool Player::operator<(const Player& p) const {

    if(this->name() == p.name()) {
      // Same, by ID
      if(this->birthDate() == p.birthDate()) {
        return this->id() < p.id();
      } else {
        return this->birthDate() < p.birthDate();
      }
    }
    else {
      return this->name() < p.name();
    }
    return false;

  }

  // "nimi; joukkue; syntymämaa; syntymäaika"
  // TODO: hae tiimin nimi kun ID tiedetään!
  std::ostream& operator<<(std::ostream& stream, const Player& p) {
    // Haetaan tiimi
    // Nimen haku p.team.name()
    stream << p.name() << "; " << "<TIIMIN NIMI>" << ";" << p.country() << "; " << p.birthDate();
    return stream;
  }

  /**
   * Ovatko kaski Datea samat?
  */
  bool Date::operator==(const Date& d) const {
    return this->day_ == d.day() 
    && this->month_ == d.month() 
    && this->year_ == d.year();
  }



  Stat::Stat(int player_id, int assists, int goals, int games, int pm) : player_id_(player_id), assists_(assists), goals_(goals), games_(games), plus_minus_(pm) {
  }

  int Stat::player_id() const { return this->player_id_; }
  int Stat::assists() const { return this->assists_; }
  int Stat::goals() const { return this->goals_; }
  int Stat::games() const { return this->games_; }
  int Stat::plus_minus() const { return this->plus_minus_; }
  int Stat::points() const { return this->goals_ + this->assists_; } 

  double Stat::ppg() const {
    if(this->games() == 0) { return 0.0; }
    return this->points() / this->games();
  }



  // TODO:
  std::ostream& operator<<(std::ostream& virta, const Stat& s) {
    std::setprecision(2); // tulostaa kaikki intitkin?
    virta << s.points() << " points, " << s.goals() << " goals, " << s.assists() << " assists, " << s.ppg() << " points per game, plus/minus: " << s.plus_minus();
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

    // Ota kopio, jota kopeloidaan ja palautetaan
    std::vector<Stat> sCopy = this->stats_;

    if(order == "points") {
      std::sort( sCopy.begin(), sCopy.end(), cmpPlayerPoints);
    }
    else if(order=="goals") {
      std::sort(sCopy.begin(), sCopy.end(), cmpPlayerGoals);
    }
    else if(order=="assists") {
      std::sort( sCopy.begin(), sCopy.end(), cmpPlayerAssists);
    }
    else if(order=="points_per_game") {
      std::sort( sCopy.begin(), sCopy.end(), cmpPlayerPointsPerGame);
    }
    else {
      // Muutoin ID:n mukaan
      std::sort( sCopy.begin(), sCopy.end(), cmpPlayerId);
    }


    return sCopy; //this->stats_;

  }






  // -- TEAM --

  Team::Team(int id, std::string abbr, std::string name) : id_(id), abbreviation_(abbr), name_(name) {} 

  int Team::id() const { return this->id_; }
  const std::string& Team::abbreviation() const { return this->abbreviation_; }
  const std::string& Team::name() const { return this->name_; }
  // Luettelee pelaajat nimien kasvavan aakkosjärjestyksen mukaisessa järjestyksessä
  const std::vector<Player>& Team::players() const { 
    return this->players_;
  }


  void Team::add_player(const Player& p) {
    this->players_.push_back(p);
  }

  /**
   * vertailee joukkueita nimen perusteella. Jos nimet olisivat samat, verrataan toissijaisesti id-numeroita.
   */
  bool Team::operator<(const Team& team) const {

    if(this->name() != team.name()) {
      return this->name() < team.name();
    } 
    else {
      return this->id() < team.id();
    }
  }

  std::ostream& operator<<(std::ostream& stream, const Team& t) {
    stream << t.name() << " (" << t.abbreviation() << ")";
    return stream;
  }





  // -- League --

  League::League(std::string joukkuetiedosto, std::string pelaajatiedosto, std::string tilastotiedosto) {

    // Lue data: TODO:
    std::vector< std::vector<std::string> > teamData   = lueTiedosto(joukkuetiedosto); // id, lyhenne, nimi
    std::vector< std::vector<std::string> > playerData = lueTiedosto(pelaajatiedosto); // id, joukkuenimi, id;joukkueen id;nimi; pelipaikka; syntymämaa; syntymäaika
    std::vector< std::vector<std::string> > statsData  = lueTiedosto(tilastotiedosto); // pelaajan id; syötöt; maalit; pelit; plus-miinus



    // Luo kutakin tiedoston riviä vastaavat oliot for-loopeissa ja tallenna
    for (size_t t_i=0; t_i < teamData.size(); ++t_i) {
      
      /*std::cout << "Tiimi: " << strToInt(teamData.at(t_i).at(0)) <<
        teamData.at(t_i).at(1) <<
          teamData.at(t_i).at(2) << std::endl;
      */

      // Luo tiimi-olio
      Team tiimi( 
        strToInt(teamData.at(t_i).at(0)),
        teamData.at(t_i).at(1),
        teamData.at(t_i).at(2)
      );

      this->teams_.push_back( tiimi );

      // DEBUG
      std::cout << tiimi << std::endl;

    }

    std::cout << "-- Tiimit luettu " << std::endl;

    // Sama Playereille
    for (size_t p_i=0; p_i < playerData.size(); ++p_i) {
      
      // DEBUG
      std::cout << "bday: '" <<  playerData.at(p_i).at(5) << "'\n";

      int team_id = strToInt( playerData.at(p_i).at(1) );
      
      //std::cout << "Kuuluu tiimiin: " << this->get_team( team_id ) << std::endl;
      

      // Anna pelaajalle tiimi-viite. Lähinnä siksi että voidaan hakea nimi tulostukseen
      //Team& team = this->get_team( team_id );

      // Luo pelaaja-olio
      Player pelaaja( 
        strToInt( playerData.at(p_i).at(0) ), // id
        team_id, // team id
        playerData.at(p_i).at(2),               // name
        playerData.at(p_i).at(3).c_str()[0], // pos
        playerData.at(p_i).at(4), // counrty
        dateFromString( playerData.at(p_i).at(5) )
      );

      // Lisää pelaaja Leaguen tiimien pelaajalistaan
      this->get_team( team_id ).add_player( pelaaja );
      // lisää pelaaja Liigaan
      this->players_.push_back( pelaaja );

    
      // DEBUG
      std::cout << pelaaja << std::endl;

    }

    std::cout << "-- Pelaajat luettu " << std::endl;


    // Ja sama statseille
    for (size_t s_i=0; s_i < statsData.size(); ++s_i) {

      // DEBUG
      std::cout << s_i << "::" 
      << strToInt( statsData.at(s_i).at(0) )
      << "," << strToInt( statsData.at(s_i).at(1) )
      << "," << strToInt( statsData.at(s_i).at(2) )
      << "," << strToInt( statsData.at(s_i).at(3) )
      << "," << strToInt( statsData.at(s_i).at(4) ) << std::endl;
      


      // Yksittäinen Stat-olio
      Stat statsi(
        strToInt( statsData.at(s_i).at(0) ), // p id
        strToInt( statsData.at(s_i).at(1) ), // syötöt
        strToInt( statsData.at(s_i).at(2) ), // maalit
        strToInt( statsData.at(s_i).at(3) ), // pelit
        strToInt( statsData.at(s_i).at(4) ) // +-
      );

      // DEBUG
      //std::cout << statsi << std::endl; // !

      this->stats_.push( statsi );

    }
    
    // Sorttaa vielä: 
    std::sort( this->players_.begin(), this->players_.end() );

    std::cout << "Konstruktori valmis! Data luettu\n\n";

  }


  // Luettelee joukkueet joukkueiden lyhenteiden kasvavan aakkosjärjestyksen mukaisessa järjestyksessä.
  const std::vector<Team>& League::teams() const {

    //std::vector<Team> tCopy = this->teams_; 
    //std::sort( tCopy.begin(), tCopy.end(), cmpTeamsAbbr );
    return this->teams_;
  }

  const std::vector<Player>& League::players() const {
    return this->players_;
  }

  const Stats& League::stats() const {
    return this->stats_;
  }


  Team& League::get_team(int id_) {

    for(unsigned i = 0; i < this->teams_.size(); ++i) {
      if( this->teams_[i].id() == id_ ) {
        return this->teams_.at(i);
      }
    }
    // Mitä jos ei löydykään?
    return this->teams_.at(0);


  }


    // Apumetodi joka lukee erotinmerkillä erotetut asiat vektoriin
  std::vector<std::string> split(const std::string erotin,  std::string rivi) {

    unsigned int position = 0;
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


  Date dateFromString(std::string& str) {
    std::vector<std::string> v = split("-", str);
    std::cout << v.size();
    std::cout << v.at(2);


    return Date(
      strToInt(v.at(2)), 
      strToInt(v.at(1)), 
      strToInt(v.at(0))
    );
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
      while( getline(ifs, rivi) ) {
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

  // Laskeva. suurin ensin
  bool cmpPlayerPoints(const Stat& p1, const Stat& p2) { 


    if( p1.points() == p2.points() ) { return cmpPlayerId(p1, p2); }
    return p1.points() > p2.points();
  }

  // Laskeva
  bool cmpPlayerGoals(const Stat& s1, const Stat& s2) { 
    if( s1.goals() == s2.goals() ) { 
       return cmpPlayerId(s1,s2);
    }
    return s1.goals() > s2.goals();
  }

  // Laskeva
  bool cmpPlayerAssists(const Stat& s1, const Stat& s2) { 
    if(  s1.assists() == s2.assists()) {
      return  cmpPlayerId(s1,s2);
    }
    return s1.assists() > s2.assists();
  }

  // Laskeva
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