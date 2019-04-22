/***************************************************************************
  tag: Erwin Aertbelien  Mon May 10 19:10:36 CEST 2004  trajectory_segment.cxx

                        trajectory_segment.cxx -  description
                           -------------------
    begin                : Mon May 10 2004
    copyright            : (C) 2004 Erwin Aertbelien
    email                : erwin.aertbelien@mech.kuleuven.ac.be

 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/
/*****************************************************************************
 *  \author
 *  	Erwin Aertbelien, Div. PMA, Dep. of Mech. Eng., K.U.Leuven
 *
 *  \version
 *		ORO_Geometry V0.2
 *
 *	\par History
 *		- $log$
 *
 *	\par Release
 *		$Id: trajectory_segment.cpp,v 1.1.1.1.2.7 2003/07/23 16:44:26 psoetens Exp $
 *		$Name:  $
 ****************************************************************************/


#include "trajectory_segment.hpp"


namespace KDL {


Trajectory_Segment::Trajectory_Segment(Path* _geom, VelocityProfile* _motprof, bool _aggregate):
	this->motprof(_motprof),this->geom(_geom), this->aggregate(_aggregate)
{
    // assume everything is set or at least check if Duration() != 0
}

Trajectory_Segment::Trajectory_Segment(Path* _geom, VelocityProfile* _motprof, double _duration, bool _aggregate):
	this->motprof(_motprof),this->geom(_geom), this->aggregate(_aggregate)
{
    // the duration was specified so assume motprof not yet set.
    this->motprof->SetProfileDuration(0, this->geom->PathLength(), _duration);
}


double Trajectory_Segment::Duration() const
{
	return this->motprof->Duration();
}

Frame Trajectory_Segment::Pos(double time) const
{
	return this->geom->Pos(this->motprof->Pos(time));
}

Twist Trajectory_Segment::Vel(double time) const
{
	return this->geom->Vel(this->motprof->Pos(time),this->motprof->Vel(time));
}

Twist Trajectory_Segment::Acc(double time) const
{
	return this->geom->Acc(this->motprof->Pos(time),this->motprof->Vel(time),this->motprof->Acc(time));
}


void Trajectory_Segment::Write(std::ostream& os) const
{
	os << "SEGMENT[ " << std::endl;
	os << "  ";this->geom->Write(os);os << std::endl;
	os << "  ";this->motprof->Write(os);os << std::endl;
	os << "]";
}

Trajectory_Segment::~Trajectory_Segment()
{
    if (this->aggregate)
        {
            delete this->motprof;
            delete this->geom;
        }
}
Path* Trajectory_Segment::GetPath() {
	return this->geom;
}

VelocityProfile* Trajectory_Segment::GetProfile() {
	return this->motprof;
}


}
