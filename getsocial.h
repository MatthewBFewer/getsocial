#ifndef GETSOCIAL_H
#define GETSOCIAL_H

typedef struct {
    const char *option;
    const char *name;
    const char *url;
} SocialProfile;


// Add your URLs to this array (or technically anything that you want copied to your clipboard)
// these are example links, you are going to want to replace these with your own
static const SocialProfile profiles[] = {
    {"-g", "GitHub",   "https://github.com/MatthewBFewer"},
    {"-l", "LinkedIn", "https://www.linkedin.com/in/matthew-fewer-246094343/"}
    
};

#define INSTRUCTIONS "Usage: getsocial [-g | -l]\n  -g  Copy GitHub profile link\n  -l  Copy LinkedIn profile link\n"

#define PROFILE_COUNT (sizeof(profiles) / sizeof(profiles[0]))

#endif // GETSOCIAL_H
