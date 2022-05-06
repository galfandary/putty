#include "putty.h"

#define DEFAULT_HOME "c:/docs"

static char s_cfg[256][16][64];
static int n_cfg = 0, i_row = 2, n_col = 0;

static FILE *configFile()
{
    FILE *fp; char file[256];
    if (!GetEnvironmentVariable("HOME", file, sizeof(file)))
        strcpy(file, DEFAULT_HOME);
    strcat(file, "/.putty"); fp = fopen(file, "r");
    return fp;
}

static void readConfig()
{
    FILE *fp; char *c, e[4], name[256];
    int i = 0, n; if (n_cfg || !(fp = configFile())) return;
    while ((n = fscanf(fp, "%[^,],%[\r\n]", c = s_cfg[n_cfg][i++], e)) > 0) {
        if (*c == '!') *c = 0;
        if (n < 2) continue;
        if (!n_col) n_col = i;
        sprintf(name, "[%02d] %s", n_cfg - 1, s_cfg[n_cfg][0]);
        strcpy(s_cfg[n_cfg][0], name);
        i = 0; n_cfg++;
    }
    fclose(fp);
}

static void os(const char *sessionname)
{
    readConfig();
    i_row = 1;
    if (!sessionname) return;
    i_row = n_cfg;
    while (i_row--)
        if (!strcmp(sessionname, &s_cfg[i_row][0][0]))
            return;
    i_row = 1;
}

static bool es(strbuf *buffer)
{
    readConfig();
    if (i_row >= n_cfg) return false;
    char c, *s = s_cfg[i_row++][0];
    while ((c = *s++)) put_byte(buffer, c);
    return true;
}

static char *getValue(const char *key)
{
    int i = n_col;
    while (i--) if (!strcmp(key, s_cfg[0][i])) return s_cfg[i_row][i];
    return 0;
}

static char *rs(const char *key, char *buffer)
{
    char *v = getValue(key); return v ? strcpy(buffer, v) : 0;
}

static int ri(const char *key, int defvalue)
{
    char *v = getValue(key); return v ? atoi(v) : strcmp("X11Forward", key) ? defvalue : 1;
}

void *open_settings_w(const char *sessionname, char **errmsg) { return s_cfg; }
void write_setting_s(void *handle, const char *key, const char *value) {}
void write_setting_i(void *handle, const char *key, int value) {}
void write_setting_filename(void *handle, const char *key, Filename *file) {}
void write_setting_fontspec(void *handle, const char *key, FontSpec *font) {}
void close_settings_w(void *handle) {}

void *open_settings_r(const char *sessionname) { os(sessionname); return s_cfg; }
char *read_setting_s(void *handle, const char *key) { return dupstr(getValue(key)); }
int read_setting_i(void *handle, const char *key, int defvalue) { return ri(key, defvalue); }
Filename *read_setting_filename(void *handle, const char *name)
{
    char *path = read_setting_s(handle, name);
    if (path) {
        Filename *ret = snew(Filename);
        ret->path = path;
        return ret;
    }
	return 0;
}
FontSpec *read_setting_fontspec(void *handle, const char *name) { return 0; }
void close_settings_r(void *handle) {}

void del_settings(const char *sessionname) {}
void *enum_settings_start() { i_row = 2; return s_cfg; }
bool enum_settings_next(void *handle, strbuf *buffer) { return es(buffer); }
void enum_settings_finish(void *handle) {}
int check_stored_host_key(const char *host, int p, const char *type, const char *key) { return 0; }
bool have_ssh_host_key(const char *hostname, int port, const char *keytype) { return 0; }
void store_host_key(const char *hostname, int port, const char *keytype, const char *key) {}
typedef void (*noise_consumer_t) (void *data, int len);
void read_random_seed(noise_consumer_t consumer) {}
void write_random_seed(void *data, int len) {}
void cleanup_all() {}

int add_to_jumplist_registry(const char *item) { return 0; }
int remove_from_jumplist_registry(const char *item) { return 0; }
char *get_jumplist_registry_entries() { char *l = snewn(2, char); l[0] = l[1] = 0; return l; }

struct host_ca_enum *enum_host_ca_start() { return 0; }
bool enum_host_ca_next(struct host_ca_enum *handle, strbuf *out) { return false; }
void enum_host_ca_finish(struct host_ca_enum *handle) {}

struct host_ca *host_ca_load(const char *name) { return 0; }
char *host_ca_save(struct host_ca *handle) { return 0; }
char *host_ca_delete(const char *name) { return 0; }

struct host_ca *host_ca_new() { return 0; }
void host_ca_free(host_ca *handle) {}
