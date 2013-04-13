#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__

#include <process/registers.h>

#include <iostream>
#include <vector>

namespace manticore { namespace serialize {

std::ostream & operator<<(std::ostream & out, manticore::process::RegisterPtr const & reg);
std::ostream & operator<<(std::ostream & out, std::vector<manticore::process::RegisterPtr> const & regs);

std::istream & operator>>(std::istream & out, manticore::process::RegisterPtr & reg);
std::istream & operator>>(std::istream & out, std::vector<manticore::process::RegisterPtr> & regs);

} }

#endif /*__SERIALIZE_H__*/
