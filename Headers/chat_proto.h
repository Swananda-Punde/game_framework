#ifndef CHAT_PROTO
#define CHAT_PROTO

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
		string get_from()
		{
			return from;
		}
		string get_msg()
		{
			return msg;
		}
};
#endif
