/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**  FairMCPoint.h
 * This is the base class for all MC Points generated by the transport of
 * tracks through active detectors.
 **/



#ifndef FAIRMCPOINT_H
#define FAIRMCPOINT_H

#include "FairMultiLinkedData.h"        // for FairMultiLinkedData

#include "Rtypes.h"                     // for Double_t, Double32_t, Int_t, etc
#include "TVector3.h"                   // for TVector3


#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class FairMCPoint : public FairMultiLinkedData
{

  public:

    /** Default constructor **/
    FairMCPoint();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Point coordinates [cm]
     *@param mom      Momentum of track at MCPoint [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     *@param EventId  MC event id
     **/
    FairMCPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                Double_t tof, Double_t length, Double_t eLoss, UInt_t EventId=0);
    
    /** Destructor **/
    virtual ~FairMCPoint();


    /** Accessors */
    UInt_t   GetEventID()    const { return fEventId; }        /// event identifier
    Int_t    GetTrackID()    const { return fTrackID; }
    Double_t GetPx()         const { return fPx; }
    Double_t GetPy()         const { return fPy; }
    Double_t GetPz()         const { return fPz; }
    Double_t GetTime()       const { return fTime; }
    Double_t GetLength()     const { return fLength; }
    Double_t GetEnergyLoss() const { return fELoss; }
    void Momentum(TVector3& mom) { mom.SetXYZ(fPx, fPy, fPz); }
    Int_t    GetDetectorID()   const { return fDetectorID;             };
    Double_t GetX()             const { return fX;                      };
    Double_t GetY()             const { return fY;                      };
    Double_t GetZ()             const { return fZ;                      };
    void Position(TVector3& pos)       const;




    /** Modifiers **/
    void SetEventID(UInt_t eventId) { fEventId = eventId; }
    virtual void SetTrackID(Int_t id) { fTrackID = id;}
    void SetTime(Double_t time)        { fTime = time; }
    void SetLength(Double_t length)    { fLength = length; }
    void SetEnergyLoss(Double_t eLoss) { fELoss = eLoss; }
    void SetMomentum(const TVector3& mom);
    void SetDetectorID(Int_t detID) { fDetectorID = detID; }
    void SetX(Double_t x) { fX = x; }
    void SetY(Double_t y) { fY = y; }
    void SetZ(Double_t z) { fZ = z; }
    void SetXYZ(Double_t x, Double_t y, Double_t z);
    void SetPosition(const TVector3& pos);


    /** Output to screen **/
    virtual void Print(const Option_t* opt = 0) const;


    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) 
    {
        //ar & boost::serialization::base_object<FairMultiLinkedData>(*this);
        ar & fTrackID;
        ar & fEventId;
        ar & fDetectorID; 
        ar & fX;
        ar & fY;
        ar & fZ;
        ar & fPx;
        ar & fPy;
        ar & fPz; 
        ar & fTime; 
        ar & fLength; 
        ar & fELoss; 
    }

  protected:

    #ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;

    #endif // for BOOST serialization
    
    Int_t fTrackID;               ///< Track index
    UInt_t fEventId;              ///< MC Event id
    Double32_t fPx, fPy, fPz;     ///< Momentum components [GeV]
    Double32_t fTime;             ///< Time since event start [ns]
    Double32_t fLength;           ///< Track length since creation [cm]
    Double32_t fELoss;            ///< Energy loss at this point [GeV]
    Int_t      fDetectorID;       ///< Detector unique identifier
    Double32_t fX, fY, fZ;        ///< Position of hit [cm]


    ClassDef(FairMCPoint,5)

};


inline void FairMCPoint::SetMomentum(const TVector3& mom)
{
  fPx = mom.Px();
  fPy = mom.Py();
  fPz = mom.Pz();
}
inline void FairMCPoint::Position(TVector3& pos) const
{
  pos.SetXYZ(fX, fY, fZ);
}


inline void FairMCPoint::SetXYZ(Double_t x, Double_t y, Double_t z)
{
  fX = x;
  fY = y;
  fZ = z;
}


inline void FairMCPoint::SetPosition(const TVector3& pos)
{
  fX = pos.X();
  fY = pos.Y();
  fZ = pos.Z();
}



#endif
