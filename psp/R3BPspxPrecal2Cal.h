/******************************************************************************
 *   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2019 Members of R3B Collaboration                          *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/

// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                           R3BPspxPrecal2Cal                       -----
// -----                    Created  20-03-2017 by I. Syndikus		   -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#ifndef R3BPSPXPRECAL2CAL_H
#define R3BPSPXPRECAL2CAL_H

#include "FairTask.h"

class TClonesArray;
class R3BEventHeader;
class R3BPspxCalPar;

/**
 * Class to convert Precal data to Cal data for PSPX detector data.
 * This means: Apply gain for energy matching of all strips.
 * @author Ina Syndikus
 * @since March 20, 2016
 */

class R3BPspxPrecal2Cal : public FairTask
{
  public:
    /** Default Constructor **/
    R3BPspxPrecal2Cal();
    /** Standard Constructor **/
    R3BPspxPrecal2Cal(const char* name, Int_t iVerbose);
    /** Destructor **/
    virtual ~R3BPspxPrecal2Cal();

    virtual InitStatus Init();
    InitStatus ReInit();
    void SetParContainers();

    virtual void Exec(Option_t* option);

    virtual void FinishEvent();
    virtual void FinishTask();

  private:
    R3BEventHeader* fHeader;    // do we need that?
    TClonesArray* fPrecalItems; /**< Array holding input (Precal) data */
    TClonesArray* fCalItems;    /**< Array holding output (Cal) data */

    R3BPspxCalPar* fCalPar; /**< Parameter instance holding gain for energy correction */
    std::vector<std::vector<Float_t>> gain;

    // void CreateHistos();
    // void WriteHistos();

  public:
    ClassDef(R3BPspxPrecal2Cal, 3)
};

#endif
