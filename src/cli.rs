use clap::{Parser, ValueEnum};

#[derive(Parser, Debug)]
#[command(version, long_about = None)]
pub struct Cli {
    pub color: String,

    #[arg(long)]
    pub from_srgb: bool,

    #[arg(long)]
    pub json_dump: bool,

    #[arg(long)]
    pub verbose: bool,

    #[arg(long, default_value = "dms")]
    pub backend: BackEnd,

    #[arg(long, default_value = "dark")]
    pub mode: Mode,
}

#[derive(ValueEnum, Clone, Copy, Debug)]
pub enum BackEnd {
    Dms,
    DmsWcag,
}

impl std::fmt::Display for BackEnd {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            BackEnd::Dms => write!(f, "DMS"),
            BackEnd::DmsWcag => write!(f, "DMS-WCAG"),
        }
    }
}

#[derive(ValueEnum, Clone, Copy, Debug)]
pub enum Mode {
    Dark,
    Light,
}

impl std::fmt::Display for Mode {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Mode::Dark => write!(f, "dark"),
            Mode::Light => write!(f, "light"),
        }
    }
}
