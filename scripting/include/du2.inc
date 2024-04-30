#if defined _discord_utilities_v2_included
 #endinput
#endif
#define _discord_utilities_v2_included

#define DU_VERSION "1.0.4"

const int LEN_ID = 10;				// Channel ID length less than this value is considered invalid
const int MAX_COMMANDS = 64;		// Max commands possible in "VERIFICATION_SETTINGS" > "blocked_commands"

/**
 * Refreshes the IDs in the configuration file.
 * This function reads the configuration file, updates the IDs, and saves the changes back to the file.
 */
native void DUMain_UpdateConfig();

/**
 * Parses the configuration file for Discord Utilities v2.
 * If the configuration file is not found or there is an error parsing it, the function sets a fail state.
 */
native void DUMain_ReloadConfig();

/**
 * Checks if the configuration file has been loaded.
 *
 * @return bool - Returns true if the configuration file has been loaded, false otherwise.
 */
native bool DUMain_IsConfigLoaded();

/**
 * Get value of a variable from the configuration file
 *
 * @param key The key of the string value to retrieve.
 * @param value The buffer to store the retrieved string value.
 * @param size The size of the buffer.
 * @return Returns true if the string value was successfully retrieved, false otherwise.
 */
native bool DUMain_GetString(char[] key, char[] value, int size);

/**
 * Set value of a variable from the configuration file
 *
 * @param key The key of the string value to retrieve.
 * @param value The buffer to store the retrieved string value.
 * @param size The size of the buffer.
 * @return Returns true if the string value was successfully retrieved, false otherwise.
 */
native bool DUMain_SetString(char[] key, char[] value, int size);

/**
 * Recover the server password. (Not available if compiled for the l4d2 engine)
 *
 * @param password The array to store the server password.
 */
native void DUMain_GetServerPassword(char[] password);

/**
 * Retrieves the DiscordBot instance.
 *
 * @return The DiscordBot instance.
 */
native DiscordBot DUMain_Bot();


/**
 * This function is called when the configuration file is loaded.
 */
forward void DUMain_OnConfigLoaded();

/**
 * This function is called when the server password is changed. (Not available if compiled for the l4d2 engine)
 */
forward void DUMain_OnServerPasswordChanged(const char[] oldValue, const char[] newValue);

//du_verification
native bool DUVerification_IsChecked(int client);
native bool DUVerification_IsMember(int client);
native bool DUVerification_GetUserId(int client, char[] sUserID, int size);

forward void DUVerification_OnLinkedAccount(int client, char[] sUserID, char[] sUsername, char[] sDiscriminator);
forward void DUVerification_OnAccountRevoked(int client, char[] sUserID);
forward void DUVerification_OnClientLoaded(int client);
forward Action DUVerification_OnBlockedCommandUse(int client, char[] sCommand);


stock void Discord_EscapeString(char[] string, int maxlen, bool name = false)
{
	if(name)
	{
		ReplaceString(string, maxlen, "everyone", "everyonｅ");
		ReplaceString(string, maxlen, "here", "herｅ");
		ReplaceString(string, maxlen, "discordtag", "dｉscordtag");
	}
	ReplaceString(string, maxlen, "#", "＃");
	ReplaceString(string, maxlen, "@", "＠");
	//ReplaceString(string, maxlen, ":", "");
	ReplaceString(string, maxlen, "_", "\\_");
	ReplaceString(string, maxlen, "'", "＇");
	ReplaceString(string, maxlen, "`", "＇");
	ReplaceString(string, maxlen, "~", "∽");
	ReplaceString(string, maxlen, "\"", "＂");
}

public void DisposeObject(JSON_Object &obj)
{
	json_cleanup_and_delete(obj);
}

public SharedPlugin __pl_discord_utilities_v2 =
{
		name = "DiscordUtilitiesv2",
		file = "du_main.smx",
	#if defined REQUIRE_PLUGIN
		required = 1,
	#else
		required = 0,
	#endif
};

#if !defined REQUIRE_PLUGIN
public void __pl_discord_utilities_v2_SetNTVOptional()
{
	MarkNativeAsOptional("DUMain_Bot");
	MarkNativeAsOptional("DUParser_UpdateConfig");
	MarkNativeAsOptional("DUParser_ReloadConfig");
	MarkNativeAsOptional("DUMain_IsConfigLoaded");
	MarkNativeAsOptional("DUParser_GetString");
	MarkNativeAsOptional("DUParser_SetString");
	MarkNativeAsOptional("DU_IsChecked");
	MarkNativeAsOptional("DU_IsMember");
	MarkNativeAsOptional("DU_GetUserId");
}
#endif 
