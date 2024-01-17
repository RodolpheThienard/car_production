#include <cwchar>
#include <iostream>
#include <set>
#include <stdio.h>
#include <vector>

/* Component */

// TODO: a class for each component
class Component
{
};

/* Class Car */

class Car
{
public:
  Component roue;
  Component chassis;
  Component habitacle;
  Component reservoir;
  Component moteur;
};

/* Chain of responsability */

class Handler
{
public:
  virtual ~Handler (){};
  void
  setSuccessor (Handler *s)
  {
    private_successor = s;
  }
  Handler *
  getSuccessor ()
  {
    return private_successor;
  }
  virtual void handleRequest () = 0;

private:
  Handler *private_successor;
};

class ProductionReservoir : public Handler
{
public:
  int capacite;
  void
  handleRequest ()
  {
    std::cout << "Ajout du Réservoir" << std::endl;
    Handler *succ = this->getSuccessor ();
    if (succ)
      succ->handleRequest ();
  }
};

class ProductionHabitacle : public Handler
{
public:
  void
  handleRequest ()
  {
    std::cout << "Ajout de l'habitacle" << std::endl;
    Handler *succ = this->getSuccessor ();
    if (succ)
      succ->handleRequest ();
  }
};

class ProductionChassis : public Handler
{
public:
  void
  handleRequest ()
  {
    std::cout << "ajout du chassis" << std::endl;
    Handler *succ = this->getSuccessor ();
    if (succ)
      succ->handleRequest ();
  }
};

class ProductionRoue : public Handler
{
public:
  void
  handleRequest ()
  {
    std::cout << "Ajout des roues" << std::endl;
    Handler *succ = this->getSuccessor ();
    if (succ)
      succ->handleRequest ();
  }
};

class ProductionPorte : public Handler
{
public:
  bool fenetre_electrique;
  void
  handleRequest ()
  {
    std::cout << "ajout des portes" << std::endl;
    Handler *succ = this->getSuccessor ();
    if (succ)
      succ->handleRequest ();
  }
};

class ProductionMoteur : public Handler
{
public:
  int consommation;
  virtual void handleRequest () = 0;
};

class ProductionMoteurSport : public ProductionMoteur
{
  void
  handleRequest ()
  {
    std::cout << "ajout du moteur sport" << std::endl;
    Handler *succ = this->getSuccessor ();
    if (succ)
      succ->handleRequest ();
  }
};

class ProductionMoteurCitadine : public ProductionMoteur
{
  void
  handleRequest ()
  {
    std::cout << "ajout du moteur citadine" << std::endl;
    Handler *succ = this->getSuccessor ();
    if (succ)
      succ->handleRequest ();
  }
};

/* Singleton */

class Singleton
{
  Singleton (const Singleton &) = delete;
  Singleton &operator= (const Singleton &) = delete;

  static Singleton *
  Instance ()
  {
    if (!unique_instance)
      {
        unique_instance = new Singleton ();
      }
    else
      {
        std::cout << "constructor : L'entreprise Singleton existe déjà"
                  << std::endl;
      }
    return unique_instance;
  }

  void
  checkSingleton ()
  {
    std::cout << "checkSingleton" << std::endl;
    if (!unique_instance)
      {
        std::cout << "checkSingleton : Unique Singleton not created"
                  << std::endl;
      }
    else
      {
        std::cout << "checkSingleton : Unique Singleton already created"
                  << std::endl;
      }
  }

private:
  Singleton () { std::cout << "Entreprise Singleton" << std::endl; }
  static Singleton *unique_instance;
};

// global variable
Singleton *Singleton::unique_instance = nullptr;

/* Parking */

class Parking
{
public:
  Parking () : max_size (100), size (0) {}
  Parking (const size_t size) : max_size (size), size (0) {}
  ~Parking () {}

  void
  add_car ()
  {
    std::cout << "Voiture ajoutée au parking" << std::endl;
    size++;
  }
  void
  sell_car ()
  {
    std::cout << "Voiture retirée du parking" << std::endl;
    size--;
  }
  bool
  is_full ()
  {
    return size == max_size;
  }

private:
  size_t max_size, size;
};

/* Abstract Factory */

class AbstractFactory
{
public:
  virtual ~AbstractFactory () {}
  virtual Car *factoryMethod () = 0;

  Parking *parking = nullptr;
};

class ConcreteFactory : public AbstractFactory
{
public:
  enum class CarType
  {
    CITY,
    SPORT
  };
  CarType car_type;

  ConcreteFactory (CarType type, Parking *parking) : car_type (type)
  {
    std::cout << "ConcreteFactory" << std::endl;
    parking = parking;
    initHandler ();
  }

  void
  initHandler ()
  {
    auto handler_roue = new ProductionRoue ();
    auto handler_chassis = new ProductionChassis ();
    auto handler_porte = new ProductionPorte ();
    auto handler_moteur = new ProductionMoteurSport ();
    auto handler_habitacle = new ProductionHabitacle ();
    auto handler_reservoir = new ProductionReservoir ();

    handler_city = handler_roue;
    handler_roue->setSuccessor (handler_chassis);
    handler_chassis->setSuccessor (handler_porte);
    handler_porte->setSuccessor (handler_moteur);
    handler_moteur->setSuccessor (handler_habitacle);
    handler_habitacle->setSuccessor (handler_reservoir);

    handler_sport = handler_city;
  }

  Car *
  factoryMethod ()
  {
    Car *car = new Car ();
    switch (car_type)
      {
      case CarType::CITY:
        std::cout << "ConcreteFactory : CITY" << std::endl;
        handler_city->handleRequest ();
        break;
      case CarType::SPORT:
        std::cout << "ConcreteFactory : SPORT" << std::endl;
        handler_city->handleRequest ();
        break;
      }
    return car;
  }

private:
  Handler *handler_city;
  Handler *handler_sport;
};

/* Observer */
class Observer
{
public:
  Observer () {}
  virtual ~Observer () {}
  virtual void update () = 0;
};

constexpr const size_t end_of_experiment = 200;

/* Agenda */
class Agenda
{
public:
  Agenda (const Agenda &) = delete;
  Agenda &operator= (const Agenda &) = delete;
  static Agenda *
  instance ()
  {
    if (agenda == nullptr)
      agenda = new Agenda;
    return agenda;
  }
  void
  notify ()
  {
    if (_today >= end_of_experiment)
      return;
    nb_ends = 0;
    std::cout << "Date: " << _today << std::endl;
    if (_working_days.contains (_today))
      {
        for (auto obs = _observers.cbegin (); obs != _observers.cend (); obs++)
          {
            (*obs)->update ();
          }
      }
    else
      {
        _today++;
        notify ();
      }
  }
  void
  end_of_day (void)
  {
    nb_ends++;
    if (nb_ends == _observers.size ())
      {
        _today++;
        notify ();
      }
  }
  void
  attach_observer (Observer *obs)
  {
    _observers.push_back (obs);
  }
  void
  detach_observer (Observer *obs)
  {
    for (auto o = _observers.cbegin (); o != _observers.cend (); o++)
      {
        if (*o == obs)
          {
            _observers.erase (o);
          }
      }
  }

private:
  Agenda ()
  {
    _today = 0;
    nb_ends = 0;
    _working_days = std::set<size_t> ();
    for (size_t i = 0; i < end_of_experiment; i++)
      {
        // No production on weekends
        if (!(i % 7 == 6 || i % 7 == 5))
          {
            _working_days.insert (i);
          }
      }
  }
  size_t _today;
  size_t nb_ends;
  std::set<size_t> _working_days;
  std::vector<Observer *> _observers;
  static Agenda *agenda;
};

Agenda *Agenda::agenda = Agenda::instance ();

class ConcreteObserver : public Observer
{
public:
  ConcreteObserver (Parking *p) : parking (p) {}
  ~ConcreteObserver () {}

  void update (void);
  void
  add_factory (AbstractFactory *f)
  {
    factories.push_back (f);
  }
  void
  delete_factory (AbstractFactory *f)
  {
    for (auto o = factories.cbegin (); o != factories.cend (); o++)
      {
        if (*o == f)
          {
            factories.erase (o);
          }
      }
  }

private:
  Parking *parking;
  std::vector<AbstractFactory *> factories;
  void end_of_day (void);
};

void
ConcreteObserver::update (void)
{
  if (!parking->is_full ())
    {
      for (auto f = factories.cbegin (); f != factories.cend (); f++)
        {
          (*f)->factoryMethod ();
        }
    }
  this->end_of_day ();
}

void
ConcreteObserver::end_of_day (void)
{
  Agenda::instance ()->end_of_day ();
}

/* Main */

int
main ()
{
  //

  Parking *parking = new Parking ();
  ConcreteObserver obs = ConcreteObserver (parking);
  AbstractFactory *factory
      = new ConcreteFactory (ConcreteFactory::CarType::CITY, parking);
  obs.add_factory (factory);
  Agenda::instance ()->attach_observer (&obs);
  Agenda::instance ()->notify ();

  //
  /* auto car = factory->factoryMethod(); */
}
