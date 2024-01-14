#include <iostream>
#include <stdio.h>
#include <vector>

// Chain of responsability
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
    // std::cout << "Debut de la création de la voiture" << std::endl;
    return private_successor;
  }

  virtual void handleRequest () = 0;

private:
  Handler *private_successor;
};

class Client
{
public:
  Handler *h;
};

class Reservoir : public Handler
{
public:
  int capacite;
  void
  handleRequest ()
  {
    if (!this->getSuccessor ())
      {
        std::cout << "Request handled by Concrete Handler 1 // no successor"
                  << std::endl;
      }
    else
      {
        std::cout << "Ajout du Réservoir" << std::endl;
        this->getSuccessor ()->handleRequest ();
      }
  }
};

class Habitacle : public Handler
{
public:
  void
  handleRequest ()
  {
    if (!this->getSuccessor ())
      {
        std::cout << "Request handled by Concrete Handler 1 // no successor"
                  << std::endl;
      }
    else
      {
        std::cout << "Ajout de l'habitacle" << std::endl;
        this->getSuccessor ()->handleRequest ();
      }
  }
};

class Chassis : public Handler
{
public:
  void
  handleRequest ()
  {
    if (!this->getSuccessor ())
      {
        std::cout << "Request handled by Concrete Handler 1 // no successor"
                  << std::endl;
      }
    else
      {
        std::cout << "ajout du chassis" << std::endl;
        this->getSuccessor ()->handleRequest ();
      }
  }
};

class Roue : public Handler
{
public:
  void
  handleRequest ()
  {
    if (!this->getSuccessor ())
      {
        std::cout << "Fin du véhicule" << std::endl;
      }
    else
      {
        std::cout << "Ajout des roues" << std::endl;
        this->getSuccessor ()->handleRequest ();
      }
  }
};

class Porte : public Handler
{
public:
  bool fenetre_electrique;
  void
  handleRequest ()
  {
    if (!this->getSuccessor ())
      {
        std::cout << "Request handled by Concrete Handler 1 // no successor"
                  << std::endl;
      }
    else
      {
        std::cout << "ajout des portes" << std::endl;
        this->getSuccessor ()->handleRequest ();
      }
  }
};

class Moteur : public Handler
{
public:
  int consommation;
  virtual void handleRequest () = 0;
};

class Moteur_sport : public Moteur
{
  void
  handleRequest ()
  {
    if (!this->getSuccessor ())
      {
        std::cout << "Request handled by Concrete Handler 1 // no successor"
                  << std::endl;
      }
    else
      {
        std::cout << "ajout du moteur" << std::endl;
        this->getSuccessor ()->handleRequest ();
      }
  }
};

class Moteur_citadine : public Moteur
{
  void
  handleRequest ()
  {
    if (!this->getSuccessor ())
      {
        std::cout << "Request handled by Concrete Handler 1 // no successor"
                  << std::endl;
      }
    else
      {
        std::cout << "ajout du moteur" << std::endl;
        this->getSuccessor ()->handleRequest ();
      }
  }
};

// class Facade
// {
// public:
//   Facade ()
//   {
//     std::cout << "Construction facade" << std::endl;
//     porte = new Porte ();
//     moteur = new Moteur ();
//     chassis = new Chassis ();
//     habitacle = new Habitacle ();
//     roue = new Roue ();
//     reservoir = new Reservoir ();
//   }
//   void
//   wrapper ()
//   {
//     porte->suboperation ();
//     chassis->suboperation ();
//     habitacle->suboperation ();
//     roue->suboperation ();
//     reservoir->suboperation ();
//     moteur->suboperation ();
//   }

// private:
//   Porte *porte;
//   Chassis *chassis;
//   Habitacle *habitacle;
//   Roue *roue;
//   Reservoir *reservoir;
//   Moteur *moteur;
// };

// Singleton

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

// Observer

class Subject;

class Observer
{
public:
  Observer (const int id) : p_id (id) {}
  virtual ~Observer () {}

  virtual int getState () = 0;
  virtual void update (Subject *subject) = 0;
  virtual int getId () = 0;

protected:
  int p_id;
};

class ConcreteObserver : public Observer
{
public:
  ConcreteObserver (const int state, const int id)
      : observerState (state), Observer (id)
  {
  }
  ~ConcreteObserver () {}

  int
  getState ()
  {
    return observerState;
  }

  int
  getId ()
  {
    return p_id; // protected
  }

  void update (Subject *subject);

private:
  int observerState;
};

class Subject
{
public:
  virtual ~Subject () {}

  void
  attach (Observer *observer)
  {
    vObserver.emplace_back (observer);
  }

  void
  detach (const int id)
  {
    for (auto it = vObserver.begin (); it != vObserver.end (); ++it)
      {
        if ((*it)->getId () == id)
          {
            vObserver.erase (it);
          }
      }
  }

  void
  notify ()
  {
    for (auto observer : vObserver)
      {
        observer->update (this);
      }
  }

  virtual int getState () = 0;
  virtual void setState (const int state) = 0;

private:
  std::vector<Observer *> vObserver;
};

class ConcreteSubject : public Subject
{
public:
  ~ConcreteSubject () {}

  int
  getState ()
  {
    return subjectState;
  }

  void
  setState (const int state)
  {
    subjectState = state;
  }

private:
  int subjectState;
};

void
ConcreteObserver::update (Subject *subject)
{
  observerState = subject->getState ();
  std::cout << "Observer(id=" << p_id << ") update state to: " << observerState
            << std::endl;
}

int
main ()
{
  Client *client = new Client ();
  Chassis *chassis = new Chassis ();
  Porte *porte = new Porte ();
  Reservoir *reservoir = new Reservoir ();
  Moteur *moteur = new Moteur_sport ();
  Roue *roue = new Roue ();
  Habitacle *habitacle = new Habitacle ();

  client->h = chassis;
  chassis->setSuccessor (reservoir);
  reservoir->setSuccessor (moteur);
  moteur->setSuccessor (habitacle);
  habitacle->setSuccessor (porte);
  porte->setSuccessor (roue);

  client->h->handleRequest ();
}
