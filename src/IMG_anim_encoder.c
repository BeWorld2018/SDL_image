/*
  SDL_image:  An example image loading library for use with SDL
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <SDL3_image/SDL_image.h>

#include "IMG_anim_encoder.h"
#include "IMG_ani.h"
#include "IMG_avif.h"
#include "IMG_gif.h"
#include "IMG_libpng.h"
#include "IMG_webp.h"


IMG_AnimationEncoder *IMG_CreateAnimationEncoder(const char *file)
{
    if (!file || !*file) {
        SDL_InvalidParamError("file");
        return NULL;
    }

    SDL_PropertiesID props = SDL_CreateProperties();
    if (!props) {
        return NULL;
    }

    SDL_SetStringProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_FILENAME_STRING, file);
    IMG_AnimationEncoder *encoder = IMG_CreateAnimationEncoderWithProperties(props);
    SDL_DestroyProperties(props);
    return encoder;
}

IMG_AnimationEncoder *IMG_CreateAnimationEncoder_IO(SDL_IOStream *dst, bool closeio, const char *type)
{
    if (!dst) {
        SDL_InvalidParamError("dst");
        return NULL;
    }

    if (!type || !*type) {
        SDL_InvalidParamError("type");
        return NULL;
    }

    SDL_PropertiesID props = SDL_CreateProperties();
    if (!props) {
        return NULL;
    }

    SDL_SetPointerProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_IOSTREAM_POINTER, dst);
    SDL_SetBooleanProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_IOSTREAM_AUTOCLOSE_BOOLEAN, closeio);
    SDL_SetStringProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_TYPE_STRING, type);
    IMG_AnimationEncoder *encoder = IMG_CreateAnimationEncoderWithProperties(props);
    SDL_DestroyProperties(props);
    return encoder;
}

IMG_AnimationEncoder *IMG_CreateAnimationEncoderWithProperties(SDL_PropertiesID props)
{
    if (!props) {
        SDL_InvalidParamError("props");
        return NULL;
    }

    const char *file = SDL_GetStringProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_FILENAME_STRING, NULL);
    SDL_IOStream *dst = SDL_GetPointerProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_IOSTREAM_POINTER, NULL);
    bool closeio = SDL_GetBooleanProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_IOSTREAM_AUTOCLOSE_BOOLEAN, false);
    const char *type = SDL_GetStringProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_TYPE_STRING, NULL);
    int timebase_numerator = (int)SDL_GetNumberProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_TIMEBASE_NUMERATOR_NUMBER, 1);
    int timebase_denominator = (int)SDL_GetNumberProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_TIMEBASE_DENOMINATOR_NUMBER, 1000);

    if (!type || !*type) {
        if (file) {
            type = SDL_strrchr(file, '.');
            if (type) {
                // Skip the '.' in the file extension
                ++type;
            }
        }
        if (!type || !*type) {
            SDL_SetError("Couldn't determine file type");
            return NULL;
        }
    }

    if (timebase_numerator <= 0) {
        SDL_SetError("Time base numerator must be > 0");
        return NULL;
    }

    if (timebase_denominator <= 0) {
        SDL_SetError("Time base denominator must be > 0");
        return NULL;
    }

    if (!dst) {
        if (!file) {
            SDL_SetError("No output properties set");
            return NULL;
        }

        dst = SDL_IOFromFile(file, "wb");
        if (!dst) {
            return NULL;
        }
        closeio = true;
    }

    IMG_AnimationEncoder *encoder = (IMG_AnimationEncoder *)SDL_calloc(1, sizeof(*encoder));
    if (!encoder) {
        goto error;
    }

    encoder->dst = dst;
    encoder->start = SDL_TellIO(dst);
    encoder->closeio = closeio;
    encoder->quality = (int)SDL_GetNumberProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_QUALITY_NUMBER, -1);
    encoder->timebase_numerator = timebase_numerator;
    encoder->timebase_denominator = timebase_denominator;

    bool result = false;
    if (SDL_strcasecmp(type, "ani") == 0) {
        result = IMG_CreateANIAnimationEncoder(encoder, props);
    } else if (SDL_strcasecmp(type, "apng") == 0 || SDL_strcasecmp(type, "png") == 0) {
        result = IMG_CreateAPNGAnimationEncoder(encoder, props);
    } else if (SDL_strcasecmp(type, "avifs") == 0 || SDL_strcasecmp(type, "avif") == 0) {
        result = IMG_CreateAVIFAnimationEncoder(encoder, props);
    } else if (SDL_strcasecmp(type, "gif") == 0) {
        result = IMG_CreateGIFAnimationEncoder(encoder, props);
    } else if (SDL_strcasecmp(type, "webp") == 0) {
        result = IMG_CreateWEBPAnimationEncoder(encoder, props);
    } else {
        SDL_SetError("Unrecognized output type");
    }
    if (result) {
        return encoder;
    }

error:
    if (dst) {
        if (closeio) {
            SDL_CloseIO(dst);
        } else if (encoder && encoder->start >= 0) {
            SDL_SeekIO(dst, encoder->start, SDL_IO_SEEK_SET);
        }
    }
    if (encoder) {
        SDL_free(encoder);
    }
    return NULL;
}

bool IMG_AddAnimationEncoderFrame(IMG_AnimationEncoder *encoder, SDL_Surface *surface, Uint64 duration)
{
    if (!encoder) {
        return SDL_InvalidParamError("encoder");
    }
    if (!surface || surface->w <= 0 || surface->h <= 0) {
        return SDL_InvalidParamError("surface");
    }

    return encoder->AddFrame(encoder, surface, duration);
}

bool IMG_CloseAnimationEncoder(IMG_AnimationEncoder *encoder)
{
    if (!encoder) {
        return SDL_InvalidParamError("encoder");
    }

    bool result = encoder->Close(encoder);
    if (encoder->closeio) {
        result &= SDL_CloseIO(encoder->dst);
    }
    SDL_free(encoder);
    return result;
}

Uint64 IMG_GetEncoderDuration(IMG_AnimationEncoder *encoder, Uint64 duration, Uint64 timebase_denominator)
{
    Uint64 value = IMG_TimebaseDuration(encoder->accumulated_pts, duration, encoder->timebase_numerator, encoder->timebase_denominator, 1, timebase_denominator);
    encoder->accumulated_pts += duration;
    return value;
}

#ifdef BUILD_SDL3_IMAGE_LIBRARY
/* sdl3_image.library: sdl3.library calls the callback with its own r13,
   but our SDL calls go through the -mresident32 glue (SDL3Base read
   through r13). The caller's r13 travels in userdata and __saveds
   reloads it (__restore_r13 below, local to this file: lwz 13,0(r3)). */
struct has_metadata_ctx
{
    void *r13;          /* first: read by __restore_r13 */
    bool has_metadata;
};

asm
("\n"
"	.pushsection \".text\"\n"
"	.align 2\n"
"	.type __restore_r13, @function\n"
"__restore_r13:\n"
"	lwz 13, 0(3)\n"
"	blr\n"
"__end__restore_r13:\n"
"	.size __restore_r13, __end__restore_r13 - __restore_r13\n"
"	.popsection\n"
);

static void __saveds SDLCALL HasMetadataCallback(void *userdata, SDL_PropertiesID props, const char *name)
{
    struct has_metadata_ctx *ctx = (struct has_metadata_ctx *)userdata;

    if (SDL_strncmp(name, "SDL_image.metadata.", 19) == 0) {
        ctx->has_metadata = true;
    }
}

bool IMG_HasMetadata(SDL_PropertiesID props)
{
    struct has_metadata_ctx ctx;

    asm volatile ("mr %0,13" : "=r" (ctx.r13));
    ctx.has_metadata = false;

    if (props) {
        SDL_EnumerateProperties(props, HasMetadataCallback, &ctx);
    }
    return ctx.has_metadata;
}
#else
static void SDLCALL HasMetadataCallback(void *userdata, SDL_PropertiesID props, const char *name)
{
    bool *has_metadata = (bool *)userdata;

    if (SDL_strncmp(name, "SDL_image.metadata.", 19) == 0) {
        *has_metadata = true;
    }
}

bool IMG_HasMetadata(SDL_PropertiesID props)
{
    bool has_metadata = false;

    if (props) {
        SDL_EnumerateProperties(props, HasMetadataCallback, &has_metadata);
    }
    return has_metadata;
}
#endif

static bool IMG_EncodeAnimation(IMG_Animation *anim, SDL_IOStream *dst, bool closeio, const char *type, int quality)
{
    IMG_AnimationEncoder *encoder = NULL;
    bool result = false;

    if (!anim || !anim->count || !anim->frames || !anim->delays) {
        SDL_InvalidParamError("anim");
        goto done;
    }

    SDL_PropertiesID props = SDL_CreateProperties();
    if (!props) {
        goto done;
    }

    SDL_SetPointerProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_IOSTREAM_POINTER, dst);
    SDL_SetStringProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_TYPE_STRING, type);
    SDL_SetNumberProperty(props, IMG_PROP_ANIMATION_ENCODER_CREATE_QUALITY_NUMBER, quality);
    encoder = IMG_CreateAnimationEncoderWithProperties(props);
    SDL_DestroyProperties(props);
    if (!encoder) {
        goto done;
    }

    result = true;
    for (int i = 0; i < anim->count; ++i) {
        if (!IMG_AddAnimationEncoderFrame(encoder, anim->frames[i], anim->delays[i])) {
            result = false;
            break;
        }
    }

done:
    if (encoder) {
        result &= IMG_CloseAnimationEncoder(encoder);
    }
    if (closeio) {
        result &= SDL_CloseIO(dst);
    }
    return result;
}

bool IMG_SaveANIAnimation_IO(IMG_Animation *anim, SDL_IOStream *dst, bool closeio)
{
    return IMG_EncodeAnimation(anim, dst, closeio, "ani", -1);
}

bool IMG_SaveAPNGAnimation_IO(IMG_Animation *anim, SDL_IOStream *dst, bool closeio)
{
    return IMG_EncodeAnimation(anim, dst, closeio, "png", -1);
}

bool IMG_SaveAVIFAnimation_IO(IMG_Animation *anim, SDL_IOStream *dst, bool closeio, int quality)
{
    return IMG_EncodeAnimation(anim, dst, closeio, "avifs", quality);
}

bool IMG_SaveGIFAnimation_IO(IMG_Animation *anim, SDL_IOStream *dst, bool closeio)
{
    return IMG_EncodeAnimation(anim, dst, closeio, "gif", -1);
}

bool IMG_SaveWEBPAnimation_IO(IMG_Animation *anim, SDL_IOStream *dst, bool closeio, int quality)
{
    return IMG_EncodeAnimation(anim, dst, closeio, "webp", quality);
}
