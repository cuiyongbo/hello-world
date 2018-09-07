********************
Abstract class Usage
********************

.. code-block:: cpp

   // rocket_engine.h
   #pragma once
   
   class RocketEngine
   {
   public:
       static RocketEngine* alloc();
       static void dealloc(RocketEngine*);
   
       virtual void ignitionStep() = 0;
   
   protected:
       RocketEngine() {}
       virtual ~RocketEngine() {}
   };
   
   // rocket_engine.cpp
   #include <stdio.h>
   #include "rocket_engine.h"
   
   class RocketEngineImpl: public RocketEngine
   {
   public:
       RocketEngineImpl(): m_fuleType(0) {}
       ~RocketEngineImpl() {}
   
       virtual void ignitionStep();
   
   private:
       int m_fuleType;
   };
   
   void RocketEngineImpl::ignitionStep()
   {
       if(m_fuleType == 0)
       {
           printf("Fuel Type: solid rocket fuel.\n");
       }
       else
       {
           printf("Fuel Type: non-solid rocket fuel.\n");
       }
   }
   
   RocketEngine* RocketEngine::alloc()
   {
       return new RocketEngineImpl;
   }
   
   void RocketEngine::dealloc(RocketEngine* engine)
   {
       delete engine;
   }
   
   // main.cpp 
   #include "rocket_engine.h"
   
   int main()
   {
       RocketEngine* engine = RocketEngine::alloc();
       engine->ignitionStep();
       RocketEngine::dealloc(engine); 
       return 0;
   }

   /* compiling 
   $ g++ main.cpp rocket_engine.cpp -std=c++11
   $ ./a.out 
   Fuel Type: solid rocket fuel.
   */
