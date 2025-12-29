/*
 * # DMS backend
 *
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

use anyhow::Result;
use palette::Hsv;

use crate::{backend::{Backend, BackendStrategy, BalanceContrast, dms::calculator::AnsiResult}, colors::convert::ColorExt};

mod calculator;
mod balance_contrast;

pub type Dms = Backend<Hsv>;

pub fn derive_container(color: &Hsv) -> Hsv {
    Hsv::new(
        color.hue,
        f32::min(color.saturation * 1.834, 1.0),
        color.value * 0.463,
    )
}

impl BackendStrategy for Dms {
    fn generate(seed_color: &palette::Srgb<f32>, strategy: Option<super::BalanceContrast>) -> Result<crate::colors::unified::AnsiPaletteHex> {
        let hsv = seed_color.to_hsv();
        let base = derive_container(&hsv);

        let strategy = match strategy {
            Some(v) => v,
            None => BalanceContrast::Dps,
        };

        let (normal_text_target, secondary_target) = if strategy == BalanceContrast::Dps {
            (40.0, 35.0)
        } else {
            (4.5, 3.5)
        };

        let ansi = AnsiResult::get(&hsv, &base)?;

        Ok(
            match strategy {
                BalanceContrast::Dps => ansi.balance_dps_itself(normal_text_target, secondary_target).to_hex(),
                BalanceContrast::None => ansi.to_hex(),
            }
        )
    }
}