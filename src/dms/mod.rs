/*
 * This module is based on the **DMS color algorithm**
 * originally implemented by **DankMaterialShell**.
 * 
 * Original algorithm  
 * © 2025 Avenge Media LLC — MIT License
 * 
 * This repository provides a **clean-room reimplementation**
 * written in Rust, with **significant structural and behavioral differences**
 * from the original implementation.
 * 
 * All Rust source code in this repository:  
 * © 2025 Maachue — MIT License
*/

/*
 * NOTE:
 * Parts of this backend were developed with the assistance of a
 * **Large Language Model (LLM)**, primarily for refactoring, debugging,
 * and iterative validation during development.
 * 
 * The author is **not a color science expert**.
 *
 * This software is provided **as-is** and should be evaluated carefully
 * before use.
*/

use crate::{
    colors::{convert::ColorExt, unified::AnsiPaletteHex},
    dms::calculator::AnsiResult,
};
use anyhow::Result;
use palette::{Hsv, Srgb};

mod balance_contrast;
mod calculator;

#[allow(dead_code)]
pub enum BalanceContrastBackEnd {
    Dps,
    Wcag,
}

pub fn derive_container(color: &Hsv) -> Hsv {
    Hsv::new(
        color.hue,
        f32::min(color.saturation * 1.834, 1.0),
        color.value * 0.463,
    )
}

pub fn generate_ansi_dps(primary: &Srgb<f32>) -> Result<AnsiPaletteHex> {
    let hsv = primary.to_hsv();
    let based = derive_container(&hsv);

    const NORMAL_TEXT_TARGET: f32 = 40.0;
    const SECONDARY_TARGET: f32 = 35.0;

    let ansi = AnsiResult::get(&hsv, &based)?;

    let ansi = ansi.balance_dps_itself(NORMAL_TEXT_TARGET, SECONDARY_TARGET);

    Ok(ansi.to_hex())
}
