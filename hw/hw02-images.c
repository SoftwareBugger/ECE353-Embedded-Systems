/*
 * This file should NOT be modified.
 */

#include "hw02-images.h"

const uint8_t Bitmaps_X[] = 
{
    /* @0 'X' (19 pixels wide) */
    0xFC, 0x03, 0xE0, // ######        #####
    0xFC, 0x03, 0xE0, // ######        #####
    0xFC, 0x03, 0xE0, // ######        #####
    0xFC, 0x03, 0xE0, // ######        #####
    0xFC, 0x03, 0xE0, // ######        #####
    0xFE, 0x07, 0xE0, // #######      ######
    0x7E, 0x0F, 0xE0, //  ######     #######
    0x7F, 0x1F, 0xC0, //  #######   #######
    0x3F, 0xBF, 0x80, //   ####### #######
    0x1F, 0xFF, 0x00, //    #############
    0x0F, 0xFE, 0x00, //     ###########
    0x07, 0xFC, 0x00, //      #########
    0x03, 0xF8, 0x00, //       #######
    0x07, 0xFC, 0x00, //      #########
    0x0F, 0xFE, 0x00, //     ###########
    0x1F, 0xFF, 0x00, //    #############
    0x3F, 0xBF, 0x80, //   ####### #######
    0x7F, 0x1F, 0xC0, //  #######   #######
    0xFE, 0x0F, 0xE0, // #######     #######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
};


const uint8_t Bitmaps_O[] = 
{
    /* @0 'O' (19 pixels wide) */
    0x1F, 0xFF, 0x00, //    #############
    0x7F, 0xFF, 0xC0, //  #################
    0x7F, 0xFF, 0xC0, //  #################
    0xFF, 0xFF, 0xE0, // ###################
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFC, 0x07, 0xE0, // ######       ######
    0xFF, 0xFF, 0xE0, // ###################
    0x7F, 0xFF, 0xC0, //  #################
    0x7F, 0xFF, 0xC0, //  #################
    0x1F, 0xFF, 0x00, //    #############
};

const uint8_t tieBitmaps[] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, // ##############################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, // ###############################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, // ###############################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, // ###############################################################################################
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                                                                       ####
    0xF0, 0x00, 0x00, 0x00, 0x07, 0xF9, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                 ########  ##                                          ####
    0xF0, 0x00, 0x00, 0x00, 0x07, 0xF9, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                 ########  ##                                          ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                    ##                                                 ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                    ##                                                 ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x9F, 0x80, 0x00, 0x00, 0x00, 0x1E, // ####                                    ##     ##  ######                                  ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x99, 0xC0, 0x00, 0x00, 0x00, 0x1E, // ####                                    ##     ##  ##  ###                                 ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x99, 0xC0, 0x00, 0x00, 0x00, 0x1E, // ####                                    ##     ##  ##  ###                                 ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x9F, 0xC0, 0x00, 0x00, 0x00, 0x1E, // ####                                    ##     ##  #######                                 ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x9F, 0xC0, 0x00, 0x00, 0x00, 0x1E, // ####                                    ##     ##  #######                                 ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x98, 0xC0, 0x00, 0x00, 0x00, 0x1E, // ####                                    ##     ##  ##   ##                                 ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x99, 0xC0, 0x00, 0x00, 0x00, 0x1E, // ####                                    ##     ##  ##  ###                                 ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x9F, 0x80, 0x00, 0x00, 0x00, 0x1E, // ####                                    ##     ##  ######                                  ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                                                                       ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                                                                       ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                                                                       ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                                                                       ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                                                                       ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                                                                       ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                                                                       ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                                                                       ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, // ####                                                                                       ####
    0xF0, 0x00, 0x18, 0x00, 0x06, 0x00, 0x00, 0xC0, 0x00, 0x30, 0x00, 0x1E, // ####               ##                ##                 ##                ##               ####
    0xF0, 0x00, 0x0C, 0x00, 0x0E, 0x00, 0x00, 0xE0, 0x00, 0x60, 0x00, 0x1E, // ####                ##              ###                 ###              ##                ####
    0xF0, 0x07, 0xCC, 0x00, 0x0C, 0x06, 0x0C, 0x60, 0x00, 0x67, 0xC0, 0x1E, // ####         #####  ##              ##       ##     ##   ##              ##  #####         ####
    0xF0, 0x00, 0x0C, 0x00, 0x0C, 0x63, 0x0C, 0x60, 0x00, 0x60, 0x00, 0x1E, // ####                ##              ##   ##   ##    ##   ##              ##                ####
    0xF0, 0x00, 0x06, 0x00, 0x0C, 0x23, 0x8C, 0x60, 0x00, 0xC0, 0x00, 0x1E, // ####                 ##             ##    #   ###   ##   ##             ##                 ####
    0xF0, 0x00, 0x06, 0x00, 0x0C, 0x30, 0x08, 0x60, 0x00, 0xC0, 0x00, 0x1E, // ####                 ##             ##    ##        #    ##             ##                 ####
    0xF0, 0x00, 0x03, 0x00, 0x0C, 0x00, 0x18, 0x60, 0x00, 0x80, 0x00, 0x1E, // ####                  ##            ##             ##    ##             #                  ####
    0xF0, 0x00, 0x03, 0x00, 0x0C, 0x00, 0x18, 0x60, 0x01, 0x80, 0x00, 0x1E, // ####                  ##            ##             ##    ##            ##                  ####
    0xF0, 0x00, 0x03, 0x00, 0x0C, 0x00, 0x30, 0x60, 0x01, 0x80, 0x00, 0x1E, // ####                  ##            ##            ##     ##            ##                  ####
    0xF0, 0x00, 0x01, 0x00, 0x0C, 0x00, 0x70, 0x60, 0x03, 0x80, 0x00, 0x1E, // ####                   #            ##           ###     ##           ###                  ####
    0xF0, 0x00, 0x01, 0x80, 0x0C, 0x00, 0xC0, 0x60, 0x03, 0x00, 0x00, 0x1E, // ####                   ##           ##          ##       ##           ##                   ####
    0xF0, 0x00, 0x01, 0x80, 0x0C, 0x03, 0x80, 0x60, 0x03, 0x00, 0x00, 0x1E, // ####                   ##           ##        ###        ##           ##                   ####
    0xF0, 0x00, 0x00, 0xC0, 0x0C, 0x0E, 0x00, 0x60, 0x06, 0x00, 0x00, 0x1E, // ####                    ##          ##      ###          ##          ##                    ####
    0xF0, 0x00, 0x00, 0xC0, 0x0C, 0x0C, 0x00, 0x60, 0x06, 0x00, 0x00, 0x1E, // ####                    ##          ##      ##           ##          ##                    ####
    0xF0, 0x00, 0x00, 0x0F, 0x8E, 0x00, 0x00, 0xE3, 0xE0, 0x00, 0x00, 0x1E, // ####                        #####   ###                 ###   #####                        ####
    0xF0, 0x00, 0x00, 0x0F, 0xCE, 0x00, 0x00, 0xE7, 0xF0, 0x00, 0x00, 0x1E, // ####                        ######  ###                 ###  #######                       ####
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, // ###############################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, // ###############################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, // ###############################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, // ###############################################################################################
    0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, //  #############################################################################################
};

/* Bitmap sizes for tie */
const uint8_t tieWidthPixels = 95;
const uint8_t tieHeightPixels = 47;


const uint8_t x_WinsBitmaps[] =
{
    0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, //  ############################################################################################
    0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, //  ############################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, // #############################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, // #############################################################################################
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                      ##    ##                                      ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                      ##    ##                                      ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                      ##    ##                                      ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                      ###  ##                                       ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                       ######                                       ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                        ####                                        ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                        ####                                        ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                       ######                                       ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                      ###  ##                                       ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                      ##    ##                                      ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                      ##    ##                                      ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                      ##    ##                                      ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x0C, 0x63, 0x70, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x78, // #####                       ##   ##   ## ###                   ###                       ####
    0xF8, 0x00, 0x00, 0x0C, 0x63, 0x70, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x78, // #####                       ##   ##   ## ###                   ###                       ####
    0xF8, 0x00, 0x00, 0x0C, 0x63, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x78, // #####                       ##   ##   ##                       ###                       ####
    0xF8, 0x00, 0x00, 0x0C, 0x63, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x78, // #####                       ##   ##   ##                       ###                       ####
    0xF8, 0x00, 0x00, 0x0C, 0x63, 0x73, 0xF9, 0xF9, 0xC0, 0x00, 0x00, 0x78, // #####                       ##   ##   ## ###  #######  ######  ###                       ####
    0xF8, 0x00, 0x00, 0x0E, 0xE6, 0x73, 0xBB, 0x19, 0xC0, 0x00, 0x00, 0x78, // #####                       ### ###  ##  ###  ### ### ##   ##  ###                       ####
    0xF8, 0x00, 0x00, 0x06, 0xF6, 0x73, 0x3B, 0x81, 0x80, 0x00, 0x00, 0x78, // #####                        ## #### ##  ###  ##  ### ###      ##                        ####
    0xF8, 0x00, 0x00, 0x06, 0xF6, 0x73, 0x39, 0xF9, 0x80, 0x00, 0x00, 0x78, // #####                        ## #### ##  ###  ##  ###  ######  ##                        ####
    0xF8, 0x00, 0x00, 0x07, 0xBC, 0x73, 0x38, 0x38, 0x00, 0x00, 0x00, 0x78, // #####                        #### ####   ###  ##  ###     ###                            ####
    0xF8, 0x00, 0x00, 0x03, 0x9C, 0x73, 0x3B, 0x19, 0xC0, 0x00, 0x00, 0x78, // #####                         ###  ###   ###  ##  ### ##   ##  ###                       ####
    0xF8, 0x00, 0x00, 0x03, 0x9C, 0x73, 0x3B, 0x99, 0xC0, 0x00, 0x00, 0x78, // #####                         ###  ###   ###  ##  ### ###  ##  ###                       ####
    0xF8, 0x00, 0x00, 0x03, 0x9C, 0x73, 0x39, 0xF9, 0xC0, 0x00, 0x00, 0x78, // #####                         ###  ###   ###  ##  ###  ######  ###                       ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, // #####                                                                                    ####
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, // #############################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, // #############################################################################################
    0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, //  ############################################################################################
    0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, //  ###########################################################################################
};

/* Bitmap sizes for x_Wins */
const uint8_t x_WinsWidthPixels = 93;
const uint8_t x_WinsHeightPixels = 46;


const uint8_t o_WinsBitmaps[] =
{
    0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, //  ####################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, // ######################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, // ######################################################################################
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                    ######                                    ####
    0xF0, 0x00, 0x00, 0x00, 0x01, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                   ########                                   ####
    0xF0, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                   ##    ##                                   ####
    0xF0, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                   ##    ##                                   ####
    0xF0, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                   ##    ##                                   ####
    0xF0, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                   ##    ##                                   ####
    0xF0, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                   ##    ##                                   ####
    0xF0, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                   ##    ##                                   ####
    0xF0, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                   ##    ##                                   ####
    0xF0, 0x00, 0x00, 0x00, 0x01, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                   ########                                   ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                    ######                                    ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x63, 0x33, 0x00, 0x00, 0x30, 0x00, 0x00, 0x3C, // ####                     ##   ##  ##  ##                  ##                      ####
    0xF0, 0x00, 0x00, 0x63, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x3C, // ####                     ##   ##  ##                      ##                      ####
    0xF0, 0x00, 0x00, 0x63, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x3C, // ####                     ##   ##  ##                      ##                      ####
    0xF0, 0x00, 0x00, 0x37, 0x33, 0x3F, 0x3F, 0x30, 0x00, 0x00, 0x3C, // ####                      ## ###  ##  ##  ######  ######  ##                      ####
    0xF0, 0x00, 0x00, 0x37, 0x33, 0x3B, 0x33, 0x30, 0x00, 0x00, 0x3C, // ####                      ## ###  ##  ##  ### ##  ##  ##  ##                      ####
    0xF0, 0x00, 0x00, 0x37, 0xA3, 0x33, 0x38, 0x30, 0x00, 0x00, 0x3C, // ####                      ## #### #   ##  ##  ##  ###     ##                      ####
    0xF0, 0x00, 0x00, 0x15, 0xE3, 0x33, 0x1F, 0x30, 0x00, 0x00, 0x3C, // ####                       # # ####   ##  ##  ##   #####  ##                      ####
    0xF0, 0x00, 0x00, 0x1D, 0xE3, 0x33, 0x03, 0x00, 0x00, 0x00, 0x3C, // ####                       ### ####   ##  ##  ##      ##                          ####
    0xF0, 0x00, 0x00, 0x1C, 0xE3, 0x33, 0x33, 0x30, 0x00, 0x00, 0x3C, // ####                       ###  ###   ##  ##  ##  ##  ##  ##                      ####
    0xF0, 0x00, 0x00, 0x1C, 0xC3, 0x33, 0x3F, 0x30, 0x00, 0x00, 0x3C, // ####                       ###  ##    ##  ##  ##  ######  ##                      ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, // ####                                                                              ####
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, // ######################################################################################
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, // ######################################################################################
    0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, //  #####################################################################################
    0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, //   ###################################################################################
};

/* Bitmap sizes for o_Wins */
const uint8_t o_WinsWidthPixels = 86;
const uint8_t o_WinsHeightPixels = 42;