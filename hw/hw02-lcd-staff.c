/**
 * @file hw02-lcd-staff.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-10-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "hw02-lcd-staff.h"

/*******************************************************************************
 * Function Name: lcd_X_wins
 ********************************************************************************
 * Summary: Prints an image indicating that player X wins
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_X_wins(void)
{
    lcd_draw_image(
        SCREEN_X / 2,
        SCREEN_Y / 2,
        x_WinsWidthPixels,
        x_WinsHeightPixels,
        x_WinsBitmaps,
        LCD_COLOR_YELLOW,
        LCD_COLOR_BLACK);
}

/*******************************************************************************
 * Function Name: lcd_O_wins
 ********************************************************************************
 * Summary: Prints an image indicating that player O wins
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_O_wins(void)
{
    lcd_draw_image(
        SCREEN_X / 2,
        SCREEN_Y / 2,
        o_WinsWidthPixels,
        o_WinsHeightPixels,
        o_WinsBitmaps,
        LCD_COLOR_YELLOW,
        LCD_COLOR_BLACK);
}

/*******************************************************************************
 * Function Name: lcd_tie
 ********************************************************************************
 * Summary: Prints an image indicating that the game ended in a tie
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_tie(void)
{
    lcd_draw_image(
        SCREEN_X / 2,
        SCREEN_Y / 2,
        tieWidthPixels,
        tieHeightPixels,
        tieBitmaps,
        LCD_COLOR_YELLOW,
        LCD_COLOR_BLACK);
}

/*******************************************************************************
 * Function Name: tic_tac_toe_example_board
 ********************************************************************************
 * Summary: Prints out an example of what the tic-tac-toe board looks like
 * Returns:
 *  Nothing
 *******************************************************************************/
void tic_tac_toe_example_board(void)
{

    // Horizontal Lines
    lcd_draw_rectangle_centered(SCREEN_CENTER_COL, UPPER_HORIZONTAL_LINE_Y, LINE_LENGTH, LINE_WIDTH, LCD_COLOR_BLUE);
    lcd_draw_rectangle_centered(SCREEN_CENTER_COL, LOWER_HORIZONTAL_LINE_Y, LINE_LENGTH, LINE_WIDTH, LCD_COLOR_BLUE);

    // Vertical Lines
    lcd_draw_rectangle_centered(LEFT_HORIZONTAL_LINE_X, SCREEN_CENTER_ROW, LINE_WIDTH, LINE_LENGTH, LCD_COLOR_BLUE);
    lcd_draw_rectangle_centered(RIGHT_HORIZONTAL_LINE_X, SCREEN_CENTER_ROW, LINE_WIDTH, LINE_LENGTH, LCD_COLOR_BLUE);

    // Top Row
    lcd_draw_image(LEFT_COL, UPPER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_RED, LCD_COLOR_BLACK);
    lcd_draw_image(CENTER_COL, UPPER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
    lcd_draw_image(RIGHT_COL, UPPER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_GREEN, LCD_COLOR_BLACK);

    // Center Row
    lcd_draw_image(LEFT_COL, CENTER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_X, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
    lcd_draw_image(CENTER_COL, CENTER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_O, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
    lcd_draw_image(RIGHT_COL, CENTER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_X, LCD_COLOR_CYAN, LCD_COLOR_BLACK);

    // Lower Row
    lcd_draw_image(LEFT_COL, LOWER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
    lcd_draw_image(CENTER_COL, LOWER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_GRAY, LCD_COLOR_BLACK);
    lcd_draw_image(RIGHT_COL, LOWER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BROWN, LCD_COLOR_BLACK);
}

// Copy and paste this function into io-lcd.c.  When you have done that, delete this the lines below
// from this file
