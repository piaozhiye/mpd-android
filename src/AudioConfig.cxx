/*
 * Copyright (C) 2003-2013 The Music Player Daemon Project
 * http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "config.h"
#include "AudioConfig.hxx"
#include "AudioFormat.hxx"
#include "AudioParser.hxx"
#include "ConfigData.hxx"
#include "ConfigGlobal.hxx"
#include "ConfigOption.hxx"
#include "util/Error.hxx"
#include "system/FatalError.hxx"

static AudioFormat configured_audio_format;

AudioFormat
getOutputAudioFormat(AudioFormat inAudioFormat)
{
	AudioFormat out_audio_format = inAudioFormat;
	out_audio_format.ApplyMask(configured_audio_format);
	return out_audio_format;
}

void initAudioConfig(void)
{
	const struct config_param *param = config_get_param(CONF_AUDIO_OUTPUT_FORMAT);

	if (param == NULL)
		return;

	Error error;
	if (!audio_format_parse(configured_audio_format, param->value,
				true, error))
		FormatFatalError("error parsing line %i: %s",
				 param->line, error.GetMessage());
}
