// Copyright 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <libmseed.h>


void usage()
{
    const char *appName = "miniseed2text";
    const char *appVersion = "0.1.0";
    const char *shortText = "Converting the miniseed file into the textual file";
    const char *usageText =
"Developer(s):"                                                         "\n"
"    2015 Durachenko Aleksey V. <durachenko.aleksey@gmail.com>"         "\n"
"Usage:"                                                                "\n"
"    miniseed2text input.mseed output.txt"                              "\n"
"Libraries:"                                                            "\n"
"    libmseed " LIBMSEED_VERSION;

    printf("%s Ver %s %s\n", appName, appVersion, shortText);
    puts(usageText);

    exit(-1);
}


int convert(const char *inputfile, const char *outputfile)
{
    FILE *output = fopen(outputfile, "w");
    if (!output)
    {
        fprintf(stderr, "can't open %s file for write\n", outputfile);
        return 1;
    }

    MSRecord *msr = 0;
    int retcode;
    while ((retcode = ms_readmsr (&msr, inputfile, -1, NULL, NULL, 1,
                   1, 0)) == MS_NOERROR)
    {
        int32_t *data_i = (int32_t *)(msr->datasamples);
        float   *data_f = (float *)(msr->datasamples);
        double  *data_d = (double *)(msr->datasamples);

        for (int64_t i = 0; i < msr->numsamples; ++i)
        {
            fprintf(output, "%s|%s|%s|%s|", msr->network, msr->station,
                   msr->channel, msr->location);

            int64_t time = (int64_t)(msr->starttime + 1000000.0*i/msr->samprate);
            fprintf(output, "%"PRId64"|", time);

            if (msr->sampletype == 'i')
                fprintf(output, "%i", data_i[i]);
            else if (msr->sampletype == 'f')
                fprintf(output, "%f", data_f[i]);
            else if (msr->sampletype == 'd')
                fprintf(output, "%f", data_d[i]);

            fprintf(output, "\n");
        }
    }

    if (retcode != MS_ENDOFFILE)
        ms_log (2, "Cannot read %s: %s\n", inputfile, ms_errorstr(retcode));

    ms_readmsr (&msr, NULL, 0, NULL, NULL, 0, 0, 0);
    fclose(output);

    if (retcode != MS_ENDOFFILE)
        return 1;

    return 0;
}


int main(int argc, char **argv)
{
    if (argc != 3)
        usage();

    const char *inputfile = argv[1];
    const char *outputfile = argv[2];

    return convert(inputfile, outputfile);
}
