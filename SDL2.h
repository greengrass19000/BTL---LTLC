//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;
//Screen dimension constants
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
    int getWidth();
    int getHeight();
    void* getPixels();
    int getPitch();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

LTexture::LTexture() {
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    //Deallocate
    free();
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

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending ) {
    //Set blending function
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
Mix_Chunk *sodd = NULL;
Mix_Chunk *seven = NULL;
Mix_Chunk *sstart = NULL;
Mix_Music *sghost1 = NULL;
Mix_Music *sghost2 = NULL;
Mix_Music *sghost3 = NULL;
Mix_Music *sghost4 = NULL;
Mix_Music *sghost5 = NULL;
Mix_Music *chaos = NULL;
Mix_Music *sdead = NULL;


void init() {
    //Initialization flag
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Init( SDL_INIT_AUDIO );
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
//    gWindow = SDL_CreateWindow( "PACMAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gWindow = SDL_CreateWindow( "PACMAN", 1475, 475, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
}

void initsound() {
	sodd = Mix_LoadWAV( "src/munch_1.wav" );
	seven = Mix_LoadWAV("src/munch_2.wav" );
	sstart = Mix_LoadWAV("src/game_start.wav");
	sghost1 = Mix_LoadMUS("src/siren_1.wav");
	sghost2 = Mix_LoadMUS("src/siren_2.wav");
	sghost3 = Mix_LoadMUS("src/siren_3.wav");
	sghost4 = Mix_LoadMUS("src/siren_4.wav");
	sghost5 = Mix_LoadMUS("src/siren_5.wav");
	chaos = Mix_LoadMUS("src/power_pellet.wav");
	sdead = Mix_LoadMUS("src/death_1.wav");
}

int beinggod = 0;
struct pairr{
	int first, second;
};
pairr sbigdot[4];
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
void checkbigdot2(int i) {
	sbigdot[i] = {-99, -99};
	Mix_PlayMusic(chaos, -1);
	beinggod = 600;
}
void checkbigdot(int pacx, int pacy) {
	for(int i = 0; i < 4; ++i) if(sbigdot[i].first != -99){
		int x = sbigdot[i].first;
		int y = sbigdot[i].second + 47;
		if(pacx == x - 5 && pacy == y - 25) checkbigdot2(i);
		if(pacx == x + 15 && pacy == y - 4) checkbigdot2(i);
		if(pacx == x - 5 && pacy == y + 15) checkbigdot2(i);
		if(pacx == x - 25 && pacy == y - 4 ) checkbigdot2(i);
	}
}