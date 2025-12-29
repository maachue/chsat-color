use std::ops::Index;

use anyhow::Result;
use palette::Srgb;

use crate::colors::{convert::ColorExt, unified::{AnsiPalette, AnsiPaletteHex}};

pub type _AnsiPaletteSrgbf32 = AnsiPalette<Srgb<f32>>;

impl _AnsiPaletteSrgbf32 {
    pub fn _to_hex(&self) -> AnsiPaletteHex {
        AnsiPaletteHex::from_array(&std::array::from_fn(|i| {
            if i < 8 {
                self.normal.index(i).to_hex()
            } else {
                self.bright.index(i - 8).to_hex()
            }
        }))
    }
}

#[allow(dead_code)]
pub struct Backend<T> {
    pub normal: [T; 8],
    pub bright: [T; 8],
}

#[derive(ValueEnum, Clone, Copy, Debug)]
pub enum BackendEnum {
    Dms,
}

impl std::fmt::Display for BackendEnum {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            BackendEnum::Dms => write!(f, "DMS"),
        }
    }
}

use clap::ValueEnum;

#[derive(PartialEq, ValueEnum, Clone, Copy, Debug)]
pub enum BalanceContrast {
    Dps,
    // Wcag,
    None,
}

pub trait BackendStrategy {
    fn generate(seed_color: &Srgb<f32>, strategy: Option<BalanceContrast>) -> Result<AnsiPaletteHex>;
}

mod dms;
pub use dms::Dms;