// --------------------------------------------------------------------
// -----          R3BMusicContFact source file                    -----
// -----     Created 24/11/19  by J.L. Rodriguez-Sanchez          -----
// --------------------------------------------------------------------
//
//  R3BMusicContFact
//
//  Factory for the parameter containers in libR3BMusic
//

#include "R3BMusicContFact.h"

#include "FairLogger.h"
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"
#include "FairRuntimeDb.h"

#include "R3BMusicCalPar.h"
#include "R3BMusicHitPar.h"

#include "TClass.h"

static R3BMusicContFact gR3BMusicContFact;

R3BMusicContFact::R3BMusicContFact()
{
    // Constructor (called when the library is loaded)
    fName = "R3BMusicContFact";
    fTitle = "Factory for parameter containers in libR3BMusic";
    setAllContainers();
    FairRuntimeDb::instance()->addContFactory(this);
}

void R3BMusicContFact::setAllContainers()
{
    // Creates the Container objects with all accepted contexts and adds them to
    // the list of containers for the STS library.

    FairContainer* p1 = new FairContainer("musicCalPar", "MUSIC Cal Parameters", "MusicCalParContext");
    p1->addContext("MusicCalParContext");

    containers->Add(p1);

    FairContainer* p2 = new FairContainer("musicHitPar", "MUSIC Hit Parameters", "MusicHitParContext");
    p2->addContext("MusicHitParContext");

    containers->Add(p2);
}

FairParSet* R3BMusicContFact::createContainer(FairContainer* c)
{
    // Trals the constructor of the corresponding parameter container.
    // For an actual context, which is not an empty string and not the default context
    // of this container, the name is concatinated with the context.

    const char* name = c->GetName();
    LOG(INFO) << "R3BMusicContFact: Create container name: " << name;
    FairParSet* p = 0;
    if (strcmp(name, "musicCalPar") == 0)
    {
        p = new R3BMusicCalPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    if (strcmp(name, "musicHitPar") == 0)
    {
        p = new R3BMusicHitPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    return p;
}

void R3BMusicContFact::activateParIo(FairParIo* io)
{
    // activates the input/output class for the parameters
    // needed by the Sts
}

ClassImp(R3BMusicContFact)
