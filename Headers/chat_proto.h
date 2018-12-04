#ifndef CHAT_PROTO
#define CHAT_PROTO

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using std::string;

class chat_proto{
	private : 
		string from, msg;
		friend class boost::serialization::access;

		template <typename Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & from;
			ar & msg;
		}
	public :
		chat_proto(string from, string msg)
		{
			this->from = from;
			this->msg = msg;
		}
		chat_proto():from{""},msg{""}
		{}
		string get_from()
		{
			return from;
		}
		string get_msg()
		{
			return msg;
		}
		void set_from(string from)
		{
			this->from = from;
		}
		void set_msg(string msg)
		{
			this->msg = msg;
		}
};
#endif
