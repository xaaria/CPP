// nhl.h
#include <iostream>
#include <string>
#include <vector>

#ifdef NHL_H
  #define NHL_H
#endif // NHL_H
/*

  C++ -Tentti 27.05.2020
  Okko Pyssysalo # 428467

*/

namespace otecpp_nhl {
  
  int strToInt(std::string& str);

  // Class Date

  class Date {

    private:
      int day_;
      int month_;
      int year_;

    public:

      Date(int d, int m, int y); 

      // Palauttaa kuukauden p‰iv‰n (kokonaisluku 1-31).
      int day() const;
      // Palauttaa kuukauden (kokonaisluku 1-12).
      int month() const;
      // Vuosi
      int year() const;
      // varhaisempi p‰iv‰m‰‰r‰ on pienempi
      bool operator<(const Date& d) const;
      bool operator==(const Date& d2) const;

    

  };

  // virta << Date
  // tulostaa Date-olion muodossa "day.month.year"
  std::ostream& operator<<(std::ostream& stream, const Date& d);


  // Apufunktio -- Palauttaa Date-obj. merkkijonosta muotoa "yyyy-mm-dd"
  Date dateFromString(std::string& str);

  class Team; // FD

  class Player {

    private:
      int id_;
      int team_id_;
      std::string name_;
      char pos_;
      std::string country_;
      Date bday;
      

    public:

      Player(int id, int team_id, std::string name, char pos, std::string country, Date bday); //, Team& t);

      int id() const;
      int team_id() const;
      const std::string& name() const;
      char position() const;
      const std::string& country() const;
      const Date& birthDate() const;

      //Team& team;
      /**
      * vertailee pelaajia ensisijaisesti nimen perusteella. Jos nimet ovat samat, 
      * verrataan toissijaisesti syntym‰aikoja. Jos nekin olisivat samat, verrataan viimeiseksi id-numeroita.
      */
      bool operator<(const Player& p) const;


  };

  // Luokan ulkopuolinen tulostus
  // tulostaa Player-olion muodossa "nimi; joukkue; syntym‰maa; syntym‰aika". Esim. Ovechkin Alex; Washington Capitals; RUS; 17.9.1985.
  std::ostream& operator<<(std::ostream& stream, const Player& p);




  /* Yll‰pit‰‰ tietoa yhden pelaajan tilastoista. HUOM, YKSIKK÷MUOTO */
  class Stat {

    private:
      int player_id_;
      int assists_;
      int goals_;
      int games_;
      int plus_minus_;

    public:

      Stat(int player_id, int assits, int goals,  int games, int plus_minus);

      int player_id() const;
      int assists() const;
      int goals() const;
      int games() const;
      // points per game
      double ppg() const;
      int points() const; 
      int plus_minus() const;

  };

  // Oheisfunktioita (luokan ulkopuolella):
  /*
    tulostaa Stat-olion muodossa
    "a points, b goals, c assists, d games, e points per game, plus/minus: f", miss‰ a, b, c, d, e ja f ovat konkreettisia lukuarvoja. 
    Pisteet per peli, eli edell‰ e,
    esitet‰‰n kahden desimaalin tarkkuudella. Esim. "66 points, 38 goals, 28 assists, 68 games, 0.97 points per game, plus/minus: 10".
  */
  std::ostream& operator<<(std::ostream& virta, const Stat& s);







  /* Yll‰pit‰‰ kaikkien pelaajien tilastoja. | HUOMAA MONIKKOMUOTO */
  class Stats {

    public:

      //Stats();

      /**
       * Palauttaa parametrin mukaisen id-numeron omaavan pelaajan Stat-olion.
       */
      Stat stat(int player_id) const;

      /**
       * Muut sallitut order-arvot ovat: goals, assists, points_per_game (ks. teht.anto)
       */ 
      std::vector<Stat> statsBy(std::string order="points") const;

      /*
        Tallentaa uuden Stat-olion this.stats vektoriin
      */
      void push(Stat stat);


    private:
      
      // vektori jossa Stat-olioita (!)
      std::vector<Stat> stats_; // kaikki tilastot

  };





  class Team {

    private:
      int id_;
      std::string abbreviation_;
      std::string name_;
      std::vector<Player> players_;


    public:

      Team(int id, std::string abbreviaton, std::string name);

      int id() const;
      const std::string& abbreviation() const;
      const std::string& name() const;
      const std::vector<Player>& players() const;
      void add_player(const Player& p); // Lis‰‰ pelaajan tiimiin, eli players_-vektoriin. Tiimin pit‰‰ olla jo olemassa!
      
      /**
       * vertailee joukkueita nimen perusteella. Jos nimet olisivat samat, verrataan toissijaisesti id-numeroita.
       */
      bool operator<(const Team& team) const;



  };

  // Oheisfunktio luokan ulkopuolella

  std::ostream& operator<<(std::ostream& stream, const Team& t);


  /* Yll‰pit‰‰ kokonaisvaltaisesti tietoa liigan joukkueista, pelaajista ja tilastoista. */
  class League {

    private:

      std::vector<Team>     teams_;
      std::vector<Player>   players_;
      Stats    stats_;

    public:

      League(std::string joukkuetiedosto, std::string pelaajatiedosto, std::string tilastotiedosto);

      const std::vector<Team>& teams() const;
      const std::vector<Player>& players() const;
      const Stats& stats() const;

      // Palauttaa viitteen tiimiin jolla id 
      Team& get_team(int id);
      

  };


  // Tiedostojen lukuun tarvittavat apumetodit:

  /* 
  * Palauttaa 2d-vektorin joss kukin solu yksi rivi pilkottuna
  */
  std::vector< std::vector<std::string> > lueTiedosto( const std::string filename);

  /**
   * Pilkkoo rivin a;b;c string-vektoriksi <"a","b","c">. J‰rjestys pysyy samana
   */
  std::vector<std::string> split(const std::string erotin=";", std::string rivi="");



  /* Vertaimet */
  bool cmpPlayerId(const Stat& s1, const Stat& s2);
  bool cmpPlayerPoints(const Stat& s1, const Stat& s2);
  bool cmpPlayerGoals(const Stat& s1, const Stat& s2);
  bool cmpPlayerAssists(const Stat& s1, const Stat& s2);
  bool cmpPlayerPointsPerGame(const Stat& s1, const Stat& s2);
  bool cmpTeamsAbbr(const Team& t1, const Team& t2);
  



} // namespace otecpp_nhl
