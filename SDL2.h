SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* loadSurface( std::string path );
SDL_Surface* gPNGSurface = NULL;
const int SCREEN_WIDTH = 447;
const int SCREEN_HEIGHT = 576;

class LTexture {
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( std::string path );
    bool loadFromFile2( std::string path );

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL );

    //Gets image dimensions
    bool lockTexture();
    bool unlockTexture();
    int getWidth();
    int getHeight();
    void* getPixels();
    int getPitch();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    void* mPixels;
    int mPitch;

    //Image dimensions
    int mWidth;
    int mHeight;
};

LTexture::LTexture() {
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mPixels = NULL;
    mPitch = 0;
}

LTexture::~LTexture() {
    //Deallocate
    free();
}

bool LTexture::lockTexture() {
    bool success = true;

    //Texture is already locked
    if( mPixels != NULL ) {
        printf( "Texture is already locked!\n" );
        success = false;
    }
    //Lock texture
    else {
        if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 ) {
            printf( "Unable to lock texture! %s\n", SDL_GetError() );
            success = false;
        }
    }

    return success;
}

bool LTexture::unlockTexture() {
    bool success = true;

    //Texture is not locked
    if( mPixels == NULL ) {
        printf( "Texture is not locked!\n" );
        success = false;
    }
    //Unlock texture
    else {
        SDL_UnlockTexture( mTexture );
        mPixels = NULL;
        mPitch = 0;
    }

    return success;
}

bool LTexture::loadFromFile( std::string path ) {
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0x00, 0x00 ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        } else {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free() {
    //Free texture if it exists
    if( mTexture != NULL ) {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void* LTexture::getPixels() {
    return mPixels;
}

int LTexture::getPitch() {
    return mPitch;
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending ) {
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha ) {
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip ) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL ) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth() {
    return mWidth;
}

int LTexture::getHeight() {
    return mHeight;
}

LTexture gSrc;
LTexture whitemap;
LTexture circle;
LTexture filler;
Mix_Chunk *sodd = NULL;
Mix_Chunk *seven = NULL;
Mix_Music *sghost1 = NULL;
Mix_Music *sghost2 = NULL;
Mix_Music *sghost3 = NULL;
Mix_Music *sghost4 = NULL;
Mix_Music *sghost5 = NULL;
Mix_Music *sstart = NULL;
Mix_Music *chaos = NULL;
Mix_Music *sdead1 = NULL;
Mix_Music *sdead2 = NULL;
Mix_Music *ghosteaten = NULL;
Mix_Chunk *fruiteaten = NULL;

struct pairr {
    int first, second;
};

int dd[480][576];
int d[480][576];
int dd2[480][576];
int boxtrace[480][576];
bool ms[] = {1, 1, 1, 1};
bool ve[480][576][4];
bool scared[4];
bool dirchanged;
int stackpoint[] = {200, 400, 800, 1600};
int mx[4];
int my[4];
//int pacx = 138;
//int pacy = 266;
int pacx = 217;
int pacy = 411;
int dmx[] = {+1, -1, 0, 0};
int dmy[] = {0, 0, -1, +1};
int mdir[] = {1, 2, 3, 3};
int dpx[] = {1, 0, -1, 0};
int dpy[] = {0, 1, 0, -1};
int lives = 3;
int point = 0;
int stage, chaseradius = 50;
int trace[447][576];
int death = 0;
int doteatean = 0;
int cnt = 0;
int beinggod = 0;
int convert[] = {0, 3, 1, 2};
int pdir = 0;
int tmpdir = -1;
int ghosteating = 0;
int beingeatenghost;
int bigdoteaten = 0;
int stack = 0;
LTexture gMap;
pairr xy[30000];
pairr sbigdot[4];
pairr sdot[241];
SDL_Rect Mon[ 4 ][ 4 ][ 2 ][ 3 ];
SDL_Rect num[10];
SDL_Rect plives = {262, 36, 19, 21};
SDL_Rect plives2 = {262, 36, 34, 25};
SDL_Rect Pac[ 4 ][ 4 ];
SDL_Rect pdead[11];
SDL_Rect ghosteatenpoint[4];
SDL_Rect GAMEOVER, READY;
SDL_Rect ifruit[8];
struct rect {
    int x, y, z, t;
} ob[41];

void init() {
    //Initialization flag
    srand(time(NULL));
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Init( SDL_INIT_AUDIO );
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
//    gWindow = SDL_CreateWindow( "PACMAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gWindow = SDL_CreateWindow( "PACMAN", 1475, 475, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
}

bool intersect(int x, int y, int l, int r) {
    if(x > l) {
        int tmp = l;
        l = x;
        x = tmp;
        tmp = r;
        r = y;
        y = tmp;
    }
    if(l <= y) {
        return true;
    }
    return false;
}

bool pcanmove(int x, int y, int z, int t) {
    for(int i = 0; i < 41; ++i)
        if(intersect(x, z, ob[i].x, ob[i].z) && intersect(y, t, ob[i].y, ob[i].t))
            return false;
    if(intersect(x, z, 165, 282) && intersect(y, t, 245, 314))
        return false;
    return true;
}

void initsound() {
    sodd = Mix_LoadWAV( "src/munch_1.wav" );
    seven = Mix_LoadWAV("src/munch_2.wav" );
    sstart = Mix_LoadMUS("src/game_start.wav");
    sghost1 = Mix_LoadMUS("src/siren_1.wav");
    sghost2 = Mix_LoadMUS("src/siren_2.wav");
    sghost3 = Mix_LoadMUS("src/siren_3.wav");
    sghost4 = Mix_LoadMUS("src/siren_4.wav");
    sghost5 = Mix_LoadMUS("src/siren_5.wav");
    ghosteaten = Mix_LoadMUS("src/eat_ghost.wav");
    fruiteaten = Mix_LoadWAV("src/eat_fruit.wav");
    chaos = Mix_LoadMUS("src/power_pellet.wav");
    sdead1 = Mix_LoadMUS("src/death_1.wav");
    sdead2 = Mix_LoadMUS("src/death_2.wav");
}

void initbigdot() {
    sbigdot[0] = {16, 48};
    sbigdot[1] = {416, 48};
    sbigdot[2] = {416, 368};
    sbigdot[3] = {16, 368};
}

void bigdot(LTexture &gSrc) {
    SDL_Rect tmp = {344, 58, 15, 15};
    for(int i = 0; i < 4; ++i) {
        gSrc.render(sbigdot[i].first, sbigdot[i].second + 47, &tmp);
    }
}

bool inbox(int num) {
    if(mx[num] >= 176 && mx[num] <= 271 && my[num] >= 219 && my[num] <= 303) {
        return true;
    }
    return false;
}

void checkbigdot2(int i) {
    sbigdot[i] = {-99, -99};
    Mix_PlayMusic(chaos, -1);
    beinggod = 600;
    point += 100;
    ++bigdoteaten;
    stack = 0;
    for(int i = 0; i < 4; ++i)
        if(!inbox(i))
            scared[i] = 1;
}

void checkbigdot(int pacx, int pacy) {
    for(int i = 0; i < 4; ++i)
        if(sbigdot[i].first != -99) {
            int x = sbigdot[i].first;
            int y = sbigdot[i].second + 47;
            if(pacx == x - 5 && pacy == y - 25)
                checkbigdot2(i);
            if(pacx == x + 15 && pacy == y - 4)
                checkbigdot2(i);
            if(pacx == x - 5 && pacy == y + 15)
                checkbigdot2(i);
            if(pacx == x - 25 && pacy == y - 4 )
                checkbigdot2(i);
        }
}

void initway() {
    xy[0] = {pacx, pacy};
    dd[pacx + 26][pacy] = 1;
    cnt = 1;
    int run = 0;
    while(run < cnt) {
        for(int dir = 0; dir < 4; ++dir) {
            int x = xy[run].first + dpx[dir];
            int y = xy[run].second + dpy[dir];
            if(x > SCREEN_WIDTH)
                x = -26;
            else if(x < -26)
                x = SCREEN_WIDTH;
            if(pcanmove(x, y, x + 25, y + 25)) {
                ve[xy[run].first + 26][xy[run].second][dir] = 1;
                if(!dd[x + 26][y]) {
                    xy[cnt++] = {x, y};
                    dd[x + 26][y] = 1;
                }
            }
        }
        ++run;
    }

    for(int i = 0; i < 600; ++i)
        for(int j = 0; j < 600; ++j)
            dd[i][j] = 0;

    ve[0][267][2] = 1;
    ve[0][267][0] = 1;
    ve[474][267][0] = 1;
    ve[474][267][2] = 1;

    GAMEOVER = {266, 344, 79, 7};
    READY = {208, 344, 46, 7};
}

void initdot() {
    sdot[ 240 ] = { 22, 22};
    sdot[ 1 ] = { 38, 22};
    sdot[ 2 ] = { 54, 22};
    sdot[ 3 ] = { 70, 22};
    sdot[ 4 ] = { 86, 22};
    sdot[ 5 ] = { 102, 22};
    sdot[ 6 ] = { 118, 22};
    sdot[ 7 ] = { 134, 22};
    sdot[ 8 ] = { 150, 22};
    sdot[ 9 ] = { 166, 22};
    sdot[ 10 ] = { 182, 22};
    sdot[ 11 ] = { 198, 22};
    sdot[ 12 ] = { 246, 22};
    sdot[ 13 ] = { 262, 22};
    sdot[ 14 ] = { 278, 22};
    sdot[ 15 ] = { 294, 22};
    sdot[ 16 ] = { 310, 22};
    sdot[ 17 ] = { 326, 22};
    sdot[ 18 ] = { 342, 22};
    sdot[ 19 ] = { 358, 22};
    sdot[ 20 ] = { 374, 22};
    sdot[ 21 ] = { 390, 22};
    sdot[ 22 ] = { 406, 22};
    sdot[ 23 ] = { 422, 22};
    sdot[ 24 ] = { 22, 38};
    sdot[ 25 ] = { 102, 38};
    sdot[ 26 ] = { 198, 38};
    sdot[ 27 ] = { 246, 38};
    sdot[ 28 ] = { 342, 38};
    sdot[ 29 ] = { 422, 38};
    sdot[ 30 ] = { 22, 70};
    sdot[ 31] = { 102, 54};
    sdot[ 32 ] = { 198, 54};
    sdot[ 33 ] = { 246, 54};
    sdot[ 34 ] = { 342, 54};
    sdot[ 35 ] = { 422, 70};
    sdot[ 36 ] = { 102, 70};
    sdot[ 37 ] = { 198, 70};
    sdot[ 38 ] = { 246, 70};
    sdot[ 39 ] = { 342, 70};
    sdot[ 40 ] = { 22, 86};
    sdot[ 41 ] = { 38, 86};
    sdot[ 42 ] = { 54, 86};
    sdot[ 43 ] = { 70, 86};
    sdot[ 44 ] = { 86, 86};
    sdot[ 45 ] = { 102, 86};
    sdot[ 46 ] = { 118, 86};
    sdot[ 47 ] = { 134, 86};
    sdot[ 48 ] = { 150, 86};
    sdot[ 49 ] = { 166, 86};
    sdot[ 50 ] = { 182, 86};
    sdot[ 51 ] = { 198, 86};
    sdot[ 52 ] = { 214, 86};
    sdot[ 53 ] = { 230, 86};
    sdot[ 54 ] = { 246, 86};
    sdot[ 55 ] = { 262, 86};
    sdot[ 56 ] = { 278, 86};
    sdot[ 57 ] = { 294, 86};
    sdot[ 58 ] = { 310, 86};
    sdot[ 59 ] = { 326, 86};
    sdot[ 60 ] = { 342, 86};
    sdot[ 61 ] = { 358, 86};
    sdot[ 62 ] = { 374, 86};
    sdot[ 63 ] = { 390, 86};
    sdot[ 64 ] = { 406, 86};
    sdot[ 65 ] = { 422, 86};
    sdot[ 66 ] = { 22, 102};
    sdot[ 67 ] = { 102, 102};
    sdot[ 68 ] = { 150, 102};
    sdot[ 69 ] = { 294, 102};
    sdot[ 70 ] = { 342, 102};
    sdot[ 71 ] = { 422, 102};
    sdot[ 72 ] = { 22, 118};
    sdot[ 73 ] = { 102, 118};
    sdot[ 74 ] = { 150, 118};
    sdot[ 75 ] = { 294, 118};
    sdot[ 76 ] = { 342, 118};
    sdot[ 77 ] = { 422, 118};
    sdot[ 78 ] = { 22, 134};
    sdot[ 79 ] = { 38, 134};
    sdot[ 80 ] = { 54, 134};
    sdot[ 81 ] = { 70, 134};
    sdot[ 82 ] = { 86, 134};
    sdot[ 83 ] = { 102, 134};
    sdot[ 84 ] = { 150, 134};
    sdot[ 85 ] = { 166, 134};
    sdot[ 86 ] = { 182, 134};
    sdot[ 87 ] = { 198, 134};
    sdot[ 88 ] = { 422, 422};
    sdot[ 89 ] = { 406, 422};
    sdot[ 90 ] = { 246, 134};
    sdot[ 91 ] = { 262, 134};
    sdot[ 92 ] = { 278, 134};
    sdot[ 93 ] = { 294, 134};
    sdot[ 94 ] = { 342, 134};
    sdot[ 95 ] = { 358, 134};
    sdot[ 96 ] = { 374, 134};
    sdot[ 97 ] = { 390, 134};
    sdot[ 98 ] = { 406, 134};
    sdot[ 99 ] = { 422, 134};
    sdot[ 100 ] = { 102, 150};
    sdot[ 101 ] = { 342, 150};
    sdot[ 102 ] = { 102, 166};
    sdot[ 103 ] = { 342, 166};
    sdot[ 104 ] = { 102, 182};
    sdot[ 105 ] = { 342, 182};
    sdot[ 106 ] = { 102, 198};
    sdot[ 107 ] = { 342, 198};
    sdot[ 108 ] = { 102, 214};
    sdot[ 109 ] = { 342, 214};
    sdot[ 110 ] = { 102, 230};
    sdot[ 111 ] = { 342, 230};
    sdot[ 112 ] = { 102, 246};
    sdot[ 113 ] = { 342, 246};
    sdot[ 114 ] = { 102, 262};
    sdot[ 115 ] = { 342, 262};
    sdot[ 116 ] = { 102, 278};
    sdot[ 117 ] = { 342, 278};
    sdot[ 118 ] = { 102, 294};
    sdot[ 119 ] = { 342, 294};
    sdot[ 120 ] = { 102, 310};
    sdot[ 121 ] = { 342, 310};
    sdot[ 122 ] = { 390, 422};
    sdot[ 123 ] = { 374, 422};
    sdot[ 124 ] = { 358, 422};
    sdot[ 125 ] = { 22, 326};
    sdot[ 126 ] = { 38, 326};
    sdot[ 127 ] = { 54, 326};
    sdot[ 128 ] = { 70, 326};
    sdot[ 129 ] = { 86, 326};
    sdot[ 130 ] = { 102, 326};
    sdot[ 131 ] = { 150, 326};
    sdot[ 132 ] = { 166, 326};
    sdot[ 133 ] = { 182, 326};
    sdot[ 134 ] = { 198, 326};
    sdot[ 135 ] = { 246, 326};
    sdot[ 136 ] = { 262, 326};
    sdot[ 137 ] = { 278, 326};
    sdot[ 138 ] = { 294, 326};
    sdot[ 139 ] = { 326, 326};
    sdot[ 140 ] = { 358, 326};
    sdot[ 141 ] = { 374, 326};
    sdot[ 142 ] = { 390, 326};
    sdot[ 143 ] = { 406, 326};
    sdot[ 144 ] = { 422, 326};
    sdot[ 145 ] = { 22, 342};
    sdot[ 146 ] = { 102, 342};
    sdot[ 147 ] = { 198, 342};
    sdot[ 148 ] = { 246, 342};
    sdot[ 149 ] = { 342, 342};
    sdot[ 150 ] = { 422, 342};
    sdot[ 151 ] = { 22, 358};
    sdot[ 152 ] = { 102, 358};
    sdot[ 153 ] = { 198, 358};
    sdot[ 154 ] = { 246, 358};
    sdot[ 155 ] = { 342, 358};
    sdot[ 156 ] = { 422, 358};
    sdot[ 157 ] = { 38, 374};
    sdot[ 158 ] = { 102, 374};
    sdot[ 159 ] = { 326, 374};
    sdot[ 160 ] = { 246, 374};
    sdot[ 161 ] = { 342, 374};
    sdot[ 162 ] = { 342, 422};
    sdot[ 163 ] = { 294, 422};
    sdot[ 164 ] = { 54, 406};
    sdot[ 165 ] = { 102, 406};
    sdot[ 166 ] = { 150, 406};
    sdot[ 167 ] = { 294, 406};
    sdot[ 168 ] = { 342, 406};
    sdot[ 169 ] = { 390, 406};
    sdot[ 170 ] = { 54, 390};
    sdot[ 171 ] = { 102, 390};
    sdot[ 172 ] = { 150, 390};
    sdot[ 173 ] = { 294, 390};
    sdot[ 174 ] = { 342, 390};
    sdot[ 175 ] = { 390, 390};
    sdot[ 176 ] = { 22, 438};
    sdot[ 177 ] = { 198, 438};
    sdot[ 178 ] = { 246, 438};
    sdot[ 179 ] = { 422, 438};
    sdot[ 180 ] = { 22, 454};
    sdot[ 181 ] = { 198, 454};
    sdot[ 182 ] = { 278, 422};
    sdot[ 183 ] = { 262, 422};
    sdot[ 184 ] = { 246, 422};
    sdot[ 185 ] = { 198, 422};
    sdot[ 186 ] = { 182, 422};
    sdot[ 187 ] = { 166, 422};
    sdot[ 188 ] = { 150, 422};
    sdot[ 189 ] = { 102, 422};
    sdot[ 190 ] = { 86, 422};
    sdot[ 191 ] = { 70, 422};
    sdot[ 192 ] = { 54, 422};
    sdot[ 193 ] = { 38, 422};
    sdot[ 194 ] = { 22, 422};
    sdot[ 195 ] = { 118, 326};
    sdot[ 196 ] = { 134, 326};
    sdot[ 197 ] = { 310, 326};
    sdot[ 198 ] = { 342, 326};
    sdot[ 199 ] = { 118, 374};
    sdot[ 200 ] = { 54, 374};
    sdot[ 201 ] = { 198, 374};
    sdot[ 202 ] = { 294, 374};
    sdot[ 203 ] = { 310, 374};
    sdot[ 204 ] = { 390, 374};
    sdot[ 205 ] = { 406, 374};
    sdot[ 206 ] = { 326, 470};
    sdot[ 207 ] = { 342, 470};
    sdot[ 208 ] = { 358, 470};
    sdot[ 209 ] = { 374, 470};
    sdot[ 210 ] = { 390, 470};
    sdot[ 211 ] = { 406, 470};
    sdot[ 212 ] = { 422, 470};
    sdot[ 213 ] = { 246, 454};
    sdot[ 214 ] = { 422, 454};
    sdot[ 215 ] = { 22, 470};
    sdot[ 216 ] = { 38, 470};
    sdot[ 217 ] = { 54, 470};
    sdot[ 218 ] = { 70, 470};
    sdot[ 219 ] = { 86, 470};
    sdot[ 220 ] = { 102, 470};
    sdot[ 221 ] = { 118, 470};
    sdot[ 222 ] = { 134, 470};
    sdot[ 223 ] = { 150, 470};
    sdot[ 224 ] = { 166, 470};
    sdot[ 225 ] = { 182, 470};
    sdot[ 226 ] = { 198, 470};
    sdot[ 227 ] = { 214, 470};
    sdot[ 228 ] = { 230, 470};
    sdot[ 229 ] = { 246, 470};
    sdot[ 230 ] = { 262, 470};
    sdot[ 231 ] = { 278, 470};
    sdot[ 232 ] = { 294, 470};
    sdot[ 233 ] = { 310, 470};
    sdot[ 234 ] = { 134, 374};
    sdot[ 235 ] = { 150, 374};
    sdot[ 236 ] = { 166, 374};
    sdot[ 237 ] = { 182, 374};
    sdot[ 238 ] = { 263, 374};
    sdot[ 239 ] = { 278, 374};
}

void initdot2() {
    trace[ 22 ][ 22 ] = 240;
    trace[ 38 ][ 22 ] = 1;
    trace[ 54 ][ 22 ] = 2;
    trace[ 70 ][ 22 ] = 3;
    trace[ 86 ][ 22 ] = 4;
    trace[ 102 ][ 22 ] = 5;
    trace[ 118 ][ 22 ] = 6;
    trace[ 134 ][ 22 ] = 7;
    trace[ 150 ][ 22 ] = 8;
    trace[ 166 ][ 22 ] = 9;
    trace[ 182 ][ 22 ] = 10;
    trace[ 198 ][ 22 ] = 11;
    trace[ 246 ][ 22 ] = 12;
    trace[ 262 ][ 22 ] = 13;
    trace[ 278 ][ 22 ] = 14;
    trace[ 294 ][ 22 ] = 15;
    trace[ 310 ][ 22 ] = 16;
    trace[ 326 ][ 22 ] = 17;
    trace[ 342 ][ 22 ] = 18;
    trace[ 358 ][ 22 ] = 19;
    trace[ 374 ][ 22 ] = 20;
    trace[ 390 ][ 22 ] = 21;
    trace[ 406 ][ 22 ] = 22;
    trace[ 422 ][ 22 ] = 23;
    trace[ 22 ][ 38 ] = 24;
    trace[ 102 ][ 38 ] = 25;
    trace[ 198 ][ 38 ] = 26;
    trace[ 246 ][ 38 ] = 27;
    trace[ 342 ][ 38 ] = 28;
    trace[ 422 ][ 38 ] = 29;
    trace[ 22 ][ 70 ] = 30;
    trace[ 102 ][ 54 ] = 31;
    trace[ 198 ][ 54 ] = 32;
    trace[ 246 ][ 54 ] = 33;
    trace[ 342 ][ 54 ] = 34;
    trace[ 422 ][ 70 ] = 35;
    trace[ 102 ][ 70 ] = 36;
    trace[ 198 ][ 70 ] = 37;
    trace[ 246 ][ 70 ] = 38;
    trace[ 342 ][ 70 ] = 39;
    trace[ 22 ][ 86 ] = 40;
    trace[ 38 ][ 86 ] = 41;
    trace[ 54 ][ 86 ] = 42;
    trace[ 70 ][ 86 ] = 43;
    trace[ 86 ][ 86 ] = 44;
    trace[ 102 ][ 86 ] = 45;
    trace[ 118 ][ 86 ] = 46;
    trace[ 134 ][ 86 ] = 47;
    trace[ 150 ][ 86 ] = 48;
    trace[ 166 ][ 86 ] = 49;
    trace[ 182 ][ 86 ] = 50;
    trace[ 198 ][ 86 ] = 51;
    trace[ 214 ][ 86 ] = 52;
    trace[ 230 ][ 86 ] = 53;
    trace[ 246 ][ 86 ] = 54;
    trace[ 262 ][ 86 ] = 55;
    trace[ 278 ][ 86 ] = 56;
    trace[ 294 ][ 86 ] = 57;
    trace[ 310 ][ 86 ] = 58;
    trace[ 326 ][ 86 ] = 59;
    trace[ 342 ][ 86 ] = 60;
    trace[ 358 ][ 86 ] = 61;
    trace[ 374 ][ 86 ] = 62;
    trace[ 390 ][ 86 ] = 63;
    trace[ 406 ][ 86 ] = 64;
    trace[ 422 ][ 86 ] = 65;
    trace[ 22 ][ 102 ] = 66;
    trace[ 102 ][ 102 ] = 67;
    trace[ 150 ][ 102 ] = 68;
    trace[ 294 ][ 102 ] = 69;
    trace[ 342 ][ 102 ] = 70;
    trace[ 422 ][ 102 ] = 71;
    trace[ 22 ][ 118 ] = 72;
    trace[ 102 ][ 118 ] = 73;
    trace[ 150 ][ 118 ] = 74;
    trace[ 294 ][ 118 ] = 75;
    trace[ 342 ][ 118 ] = 76;
    trace[ 422 ][ 118 ] = 77;
    trace[ 22 ][ 134 ] = 78;
    trace[ 38 ][ 134 ] = 79;
    trace[ 54 ][ 134 ] = 80;
    trace[ 70 ][ 134 ] = 81;
    trace[ 86 ][ 134 ] = 82;
    trace[ 102 ][ 134 ] = 83;
    trace[ 150 ][ 134 ] = 84;
    trace[ 166 ][ 134 ] = 85;
    trace[ 182 ][ 134 ] = 86;
    trace[ 198 ][ 134 ] = 87;
    trace[ 422 ][ 422 ] = 88;
    trace[ 406 ][ 422 ] = 89;
    trace[ 246 ][ 134 ] = 90;
    trace[ 262 ][ 134 ] = 91;
    trace[ 278 ][ 134 ] = 92;
    trace[ 294 ][ 134 ] = 93;
    trace[ 342 ][ 134 ] = 94;
    trace[ 358 ][ 134 ] = 95;
    trace[ 374 ][ 134 ] = 96;
    trace[ 390 ][ 134 ] = 97;
    trace[ 406 ][ 134 ] = 98;
    trace[ 422 ][ 134 ] = 99;
    trace[ 102 ][ 150 ] = 100;
    trace[ 342 ][ 150 ] = 101;
    trace[ 102 ][ 166 ] = 102;
    trace[ 342 ][ 166 ] = 103;
    trace[ 102 ][ 182 ] = 104;
    trace[ 342 ][ 182 ] = 105;
    trace[ 102 ][ 198 ] = 106;
    trace[ 342 ][ 198 ] = 107;
    trace[ 102 ][ 214 ] = 108;
    trace[ 342 ][ 214 ] = 109;
    trace[ 102 ][ 230 ] = 110;
    trace[ 342 ][ 230 ] = 111;
    trace[ 102 ][ 246 ] = 112;
    trace[ 342 ][ 246 ] = 113;
    trace[ 102 ][ 262 ] = 114;
    trace[ 342 ][ 262 ] = 115;
    trace[ 102 ][ 278 ] = 116;
    trace[ 342 ][ 278 ] = 117;
    trace[ 102 ][ 294 ] = 118;
    trace[ 342 ][ 294 ] = 119;
    trace[ 102 ][ 310 ] = 120;
    trace[ 342 ][ 310 ] = 121;
    trace[ 390 ][ 422 ] = 122;
    trace[ 374 ][ 422 ] = 123;
    trace[ 358 ][ 422 ] = 124;
    trace[ 22 ][ 326 ] = 125;
    trace[ 38 ][ 326 ] = 126;
    trace[ 54 ][ 326 ] = 127;
    trace[ 70 ][ 326 ] = 128;
    trace[ 86 ][ 326 ] = 129;
    trace[ 102 ][ 326 ] = 130;
    trace[ 150 ][ 326 ] = 131;
    trace[ 166 ][ 326 ] = 132;
    trace[ 182 ][ 326 ] = 133;
    trace[ 198 ][ 326 ] = 134;
    trace[ 246 ][ 326 ] = 135;
    trace[ 262 ][ 326 ] = 136;
    trace[ 278 ][ 326 ] = 137;
    trace[ 294 ][ 326 ] = 138;
    trace[ 326 ][ 326 ] = 139;
    trace[ 358 ][ 326 ] = 140;
    trace[ 374 ][ 326 ] = 141;
    trace[ 390 ][ 326 ] = 142;
    trace[ 406 ][ 326 ] = 143;
    trace[ 422 ][ 326 ] = 144;
    trace[ 22 ][ 342 ] = 145;
    trace[ 102 ][ 342 ] = 146;
    trace[ 198 ][ 342 ] = 147;
    trace[ 246 ][ 342 ] = 148;
    trace[ 342 ][ 342 ] = 149;
    trace[ 422 ][ 342 ] = 150;
    trace[ 22 ][ 358 ] = 151;
    trace[ 102 ][ 358 ] = 152;
    trace[ 198 ][ 358 ] = 153;
    trace[ 246 ][ 358 ] = 154;
    trace[ 342 ][ 358 ] = 155;
    trace[ 422 ][ 358 ] = 156;
    trace[ 38 ][ 374 ] = 157;
    trace[ 102 ][ 374 ] = 158;
    trace[ 326 ][ 374 ] = 159;
    trace[ 246 ][ 374 ] = 160;
    trace[ 342 ][ 374 ] = 161;
    trace[ 342 ][ 422 ] = 162;
    trace[ 294 ][ 422 ] = 163;
    trace[ 54 ][ 406 ] = 164;
    trace[ 102 ][ 406 ] = 165;
    trace[ 150 ][ 406 ] = 166;
    trace[ 294 ][ 406 ] = 167;
    trace[ 342 ][ 406 ] = 168;
    trace[ 390 ][ 406 ] = 169;
    trace[ 54 ][ 390 ] = 170;
    trace[ 102 ][ 390 ] = 171;
    trace[ 150 ][ 390 ] = 172;
    trace[ 294 ][ 390 ] = 173;
    trace[ 342 ][ 390 ] = 174;
    trace[ 390 ][ 390 ] = 175;
    trace[ 22 ][ 438 ] = 176;
    trace[ 198 ][ 438 ] = 177;
    trace[ 246 ][ 438 ] = 178;
    trace[ 422 ][ 438 ] = 179;
    trace[ 22 ][ 454 ] = 180;
    trace[ 198 ][ 454 ] = 181;
    trace[ 278 ][ 422 ] = 182;
    trace[ 262 ][ 422 ] = 183;
    trace[ 246 ][ 422 ] = 184;
    trace[ 198 ][ 422 ] = 185;
    trace[ 182 ][ 422 ] = 186;
    trace[ 166 ][ 422 ] = 187;
    trace[ 150 ][ 422 ] = 188;
    trace[ 102 ][ 422 ] = 189;
    trace[ 86 ][ 422 ] = 190;
    trace[ 70 ][ 422 ] = 191;
    trace[ 54 ][ 422 ] = 192;
    trace[ 38 ][ 422 ] = 193;
    trace[ 22 ][ 422 ] = 194;
    trace[ 118 ][ 326 ] = 195;
    trace[ 134 ][ 326 ] = 196;
    trace[ 310 ][ 326 ] = 197;
    trace[ 342 ][ 326 ] = 198;
    trace[ 118 ][ 374 ] = 199;
    trace[ 54 ][ 374 ] = 200;
    trace[ 198 ][ 374 ] = 201;
    trace[ 294 ][ 374 ] = 202;
    trace[ 310 ][ 374 ] = 203;
    trace[ 390 ][ 374 ] = 204;
    trace[ 406 ][ 374 ] = 205;
    trace[ 326 ][ 470 ] = 206;
    trace[ 342 ][ 470 ] = 207;
    trace[ 358 ][ 470 ] = 208;
    trace[ 374 ][ 470 ] = 209;
    trace[ 390 ][ 470 ] = 210;
    trace[ 406 ][ 470 ] = 211;
    trace[ 422 ][ 470 ] = 212;
    trace[ 246 ][ 454 ] = 213;
    trace[ 422 ][ 454 ] = 214;
    trace[ 22 ][ 470 ] = 215;
    trace[ 38 ][ 470 ] = 216;
    trace[ 54 ][ 470 ] = 217;
    trace[ 70 ][ 470 ] = 218;
    trace[ 86 ][ 470 ] = 219;
    trace[ 102 ][ 470 ] = 220;
    trace[ 118 ][ 470 ] = 221;
    trace[ 134 ][ 470 ] = 222;
    trace[ 150 ][ 470 ] = 223;
    trace[ 166 ][ 470 ] = 224;
    trace[ 182 ][ 470 ] = 225;
    trace[ 198 ][ 470 ] = 226;
    trace[ 214 ][ 470 ] = 227;
    trace[ 230 ][ 470 ] = 228;
    trace[ 246 ][ 470 ] = 229;
    trace[ 262 ][ 470 ] = 230;
    trace[ 278 ][ 470 ] = 231;
    trace[ 294 ][ 470 ] = 232;
    trace[ 310 ][ 470 ] = 233;
    trace[ 134 ][ 374 ] = 234;
    trace[ 150 ][ 374 ] = 235;
    trace[ 166 ][ 374 ] = 236;
    trace[ 182 ][ 374 ] = 237;
    trace[ 263 ][ 374 ] = 238;
    trace[ 278 ][ 374 ] = 239;
}

void initboxtrace() {
    //make shortest path to 211 219
    cnt = 1;
    xy[0] = {237, 219}; //+26 to avoid <0 number
    boxtrace[237][219] = 2;
    boxtrace[237][220] = 2;
    boxtrace[237][221] = 2;
    boxtrace[237][222] = 2;
    for(int i = 0; i < cnt; ++i) {
        for(int dir = 0; dir < 4; ++dir) {
            int x = xy[i].first + dpx[dir];
            int y = xy[i].second + dpy[dir];
            if(x > SCREEN_WIDTH + 26)
                x = 0;
            else if(x < 0)
                x = SCREEN_WIDTH + 26;
            if(ve[xy[i].first][xy[i].second][dir] && (!boxtrace[x][y])) {
                boxtrace[x][y] = 1 + (dir ^ 2);
                xy[cnt++] = {x, y};
            }
        }
    }
}

void showpoint2(LTexture &gSrc) {
    gSrc.render(mx[beingeatenghost], my[beingeatenghost] + 5, &ghosteatenpoint[stack-1]);
}

int lastfruit, fruit = -1;
bool fruitonmap;
int fruitpoint[8];
void reset() {
    beinggod = 0;
    pdir = 0;
    tmpdir = -1;
    ghosteating = 0;
    bigdoteaten = 0;
    stack = 0;
    pacx = 211;
    pacy = 411;
    mx[0] = 210;
    my[0] = 218;
    mx[2] = 178;
    my[2] = 266;
    mx[1] = 210;
    my[1] = 266;
    mx[3] = 243;
    my[3] = 266;
    ms[0] = ms[1] = ms[2] = ms[3] = 1;
    dirchanged = false;
    for(int i = 0; i < 4; ++i)
        scared[i] = 0;
    mdir[0] = 1;
    mdir[1] = 2;
    mdir[2] = 3;
    mdir[3] = 3;
    death = 0;
    lastfruit = 0;
    fruit = -1;
    fruitonmap = false;
}

void resetmap() {
    doteatean = bigdoteaten = 0;
    initdot();
    initdot2();
    initbigdot();
}

void showfruit(int frame) {
    if(frame - lastfruit == 600) {
        if(fruit < 7)
            ++fruit;
        fruitonmap = true;
    }
}

void checkfruit(LTexture &gSrc, int frame) {
    if(fruitonmap) {
        if(abs(pacx - 213) + abs(pacy - 313) < 3) {
            Mix_PlayChannel(-1, fruiteaten, 0);
            lastfruit = frame;
            fruitonmap = false;
            point += fruitpoint[fruit];
        } else {
            gSrc.render(213, 313, &ifruit[fruit]);
        }
    }
}
