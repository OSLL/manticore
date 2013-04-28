#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__

#include <process/registers.h>
#include <process/memory.h>

#include <iostream>
#include <vector>

namespace manticore { namespace serialize {

std::ostream & operator<<(std::ostream & out, manticore::process::MemoryRegionConstPtr const & region);
std::ostream & operator<<(std::ostream & out, manticore::process::RegisterConstPtr const & reg);

std::ostream & operator<<(std::ostream & out, std::vector<manticore::process::MemoryRegionConstPtr> const & regs);
std::ostream & operator<<(std::ostream & out, std::vector<manticore::process::RegisterConstPtr> const & regs);

std::istream & operator>>(std::istream & in, manticore::process::MemoryRegionConstPtr & reg);
std::istream & operator>>(std::istream & out, manticore::process::RegisterConstPtr & reg);

std::istream & operator>>(std::istream & in, std::vector<manticore::process::MemoryRegionConstPtr> & regs);
std::istream & operator>>(std::istream & out, std::vector<manticore::process::RegisterConstPtr> & regs);

} }

#endif /*__SERIALIZE_H__*/
