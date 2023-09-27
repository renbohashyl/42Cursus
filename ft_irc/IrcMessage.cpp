#include <cstring>
#include "IrcMessage.h"
#include "Session.h"

const char* IrcMessage::smCommandStrings[NUMERIC_COUNT] =
{
		"UNKNOWN",		
		"PASS",
		"NICK",
		"USER",
		"OPER", //yoseo: need command
		"KILL", //yoseo: need command
		"QUIT",
		"JOIN",
		"PART",
		"MODE",
		"TOPIC",
		"NAMES",
		"LIST",
		"INVITE",
		"KICK",
		"PRIVMSG",
		"PING",
		"PONG",
		"ERROR",
		"DUMMY",
		"461",
		"431",
		"432",
		"433",
		"436",
		//err_reply
		"001",
		"002",
		"003",
		"004",
		"401",
		"402",
		"403",
		"404",
		"405",
		"406",
		"407",
		"408",
		"409",
		"410",
		"411",
		"412",
		"413",
		"414",
		"415",
		"416",
		"417",
		"418",
		"419",
		"420",
		"421",
		"422",
		"423",
		"424",
		"425",
		"426",
		"427",
		"428",
		"429",
		"430",
		"434",
		"435",
		"437",
		"438",
		"439",
		"440",
		"441",
		"442",
		"443",
		"444",
		"445",
		"446",
		"447",
		"448",
		"449",
		"450",
		"451",
		"452",
		"453",
		"454",
		"455",
		"456",
		"457",
		"458",
		"459",
		"460",
		"462",
		"463",
		"464",
		"465",
		"466",
		"467",
		"468",
		"469",
		"470",
		"471",
		"472",
		"473",
		"474",
		"475",
		"476",
		"477",
		"478",
		"479",
		"480",
		"481",
		"482",
		"483",
		"484",
		"485",
		"486",
		"487",
		"488",
		"489",
		"490",
		"491",
		"492",
		"493",
		"494",
		"495",
		"496",
		"497",
		"498",
		"499",
		"500",
		"501",
		"502",
		//command response
		"300",
		"301",
		"302",
		"303",
		"304",
		"305",
		"306",
		"307",
		"308",
		"309",
		"310",
		"311",
		"312",
		"313",
		"314",
		"315",
		"316",
		"317",
		"318",
		"319",
		"320",
		"321",
		"322",
		"323",
		"324",
		"325",
		"326",
		"327",
		"328",
		"329",
		"330",
		"331",
		"332",
		"333",
		"334",
		"335",
		"336",
		"337",
		"338",
		"339",
		"340",
		"341",
		"342",
		"343",
		"344",
		"345",
		"346",
		"347",
		"348",
		"349",
		"350",
		"351",
		"352",
		"353",
		"354",
		"355",
		"356",
		"357",
		"358",
		"359",
		"360",
		"361",
		"362",
		"363",
		"364",
		"365",
		"366",
		"367",
		"368",
		"369",
		"370",
		"371",
		"372",
		"373",
		"374",
		"375",
		"376",
		"377",
		"378",
		"379",
		"380",
		"381",
		"382",
		"383",
		"384",
		"385",
		"386",
		"387",
		"388",
		"389",
		"390",
		"391",
		"392",
		"393",
		"394",
		"395",

		"200",
		"201",
		"202",
		"203",
		"204",
		"205",
		"206",
		"207",
		"208",
		"209",
		"210",
		"211",
		"212",
		"213",
		"214",
		"215",
		"216",
		"217",
		"218",
		"219",
		"220",
		"221",
		"222",
		"223",
		"224",
		"225",
		"226",
		"227",
		"228",
		"229",
		"230",
		"231",
		"232",
		"233",
		"234",
		"235",
		"236",
		"237",
		"238",
		"239",
		"240",
		"241",
		"242",
		"243",
		"244",
		"245",
		"246",
		"247",
		"248",
		"249",
		"250",
		"251",
		"252",
		"253",
		"254",
		"255",
		"256",
		"257",
		"258",
		"259",
		"260",
		"261",
		"262",
		"263",
};

IrcMessage::IrcMessage()
	: mCommand(COMMAND_UNKNOWN)
	, mPrefix()
	, mParams()
{
}
IrcMessage::IrcMessage(const IrcMessage& other)
	: mCommand(other.mCommand)
	, mPrefix(other.mPrefix)
	, mParams(other.mParams)
{
}
IrcMessage::IrcMessage(const std::string& rawMessage)
	: mCommand(COMMAND_UNKNOWN)
	, mPrefix()
	, mParams()
{
	/* FIXME */
	const std::string msg = rawMessage.substr(0, rawMessage.size() - 2);
	/* FIXME remove crlf would be not necesiry */

	size_t pos = 0;
	while (pos < msg.size() && msg[pos] == ' ')
	{
		++pos;
	}
	if (msg[pos] == ':')
	{
		while (pos < msg.size() && msg[pos] != ' ')
		{
			++pos;
		}
	}

	while (pos < msg.size() && msg[pos] == ' ')
	{
		++pos;
	}
	size_t commandPos = pos;
	while (pos < msg.size() && msg[pos] != ' ')
	{
		++pos;
	}
	mCommand = toCommand(msg.substr(commandPos, pos - commandPos));

	while (1)
	{
		while (pos < msg.size() && msg[pos] == ' ')
		{
			++pos;
		}
		if (pos == msg.size())
		{
			break;
		}
		if (msg[pos] == ':')
		{
			mParams.Add(msg.substr(pos + 1));
			break;
		}
		size_t paramPos = pos;
		while (pos < msg.size() && msg[pos] != ' ')
		{
			++pos;
		}
		mParams.Add(msg.substr(paramPos, pos - paramPos));
	}
}

IrcMessage& IrcMessage::operator=(const IrcMessage& other)
{
	mCommand = other.mCommand;
	mPrefix = other.mPrefix;
	mParams = other.mParams;
	return *this;
}

IrcMessage::~IrcMessage()
{
}

IrcMessage::eCommand IrcMessage::GetCommand() const
{
	return mCommand;
}
const std::string& IrcMessage::GetPrefix() const
{
	return mPrefix;
}
const ParamCollection& IrcMessage::GetParams() const
{
	return mParams;
}

void IrcMessage::SetCommand(eCommand command)
{
	if (command < 0 || command >= NUMERIC_COUNT)
	{
		mCommand = COMMAND_UNKNOWN;
	}
	mCommand = command;
	return;
}
void IrcMessage::SetPrefix(const std::string& prefix)
{
	mPrefix = prefix;
	return;
}
void IrcMessage::AddParam(const std::string& param)
{
	mParams.Add(param);
	return;
}

IrcMessage::eErr ForwardIrcMessage(const IrcMessage& message, Session* pSession)
{
	int remainLength = IrcMessage::MAX_LENGTH;
	remainLength -= 3;
	remainLength -= message.mPrefix.size() == 0 ? 0 : message.mPrefix.size() + 2;
	const char* commandString = IrcMessage::smCommandStrings[message.mCommand];
	size_t commandLength = strlen(commandString);
	remainLength -= commandLength;
	if (remainLength < 0)
	{
		return IrcMessage::ERR_MESSAGE_TOO_LONG;
	}
	if (message.mPrefix.size() != 0)
	{
		pSession->Send(":", 1);
		pSession->Send(message.mPrefix.c_str(), message.mPrefix.size());
		pSession->Send(" ", 1);
	}
	pSession->Send(commandString ,commandLength); 
	pSession->Send(" ", 1);
	size_t i = 1;
	for (ParamCollection::ConstIterator it = message.mParams.Begin();
			it != message.mParams.End() && remainLength > 0;
			++it, ++i)
	{
		int lengthToSend = it->size() + 1;
		if (lengthToSend > remainLength)
		{
			lengthToSend = remainLength;
		}
		if (i == message.mParams.GetSize())
		{
			pSession->Send(":", 1);
			pSession->Send(it->c_str(), lengthToSend - 1);
		}
		else
		{
			pSession->Send(it->c_str(), lengthToSend - 1);
			pSession->Send(" ", 1);
		}
		remainLength -= lengthToSend;
	}
	pSession->Send("\r\n", 2);
	return IrcMessage::ERR_NONE;
}

IrcMessage::eCommand IrcMessage::toCommand(const std::string& commandString)
{
	std::string upperCommandString = commandString;
	for (size_t pos = 0; pos < upperCommandString.size(); ++pos)
	{
		upperCommandString[pos] &= ~(0x20);
	}
	for (int i = 0; i < COMMAND_COUNT; ++i)
	{
		if (upperCommandString == smCommandStrings[i])
		{
			return static_cast<eCommand>(i);
		}
	}
	return COMMAND_UNKNOWN;
}
